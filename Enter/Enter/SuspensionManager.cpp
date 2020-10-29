#include "pch.h"
#include "SuspensionManager.h"

using namespace Enter;

using namespace concurrency;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::FileProperties;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;

Map<String^, Object^>^ SuspensionManager::_sessionState = ref new Map<String^, Object^>();

const wchar_t* SuspensionManager::sessionStateFilename = L"_sessionState.dat";

std::vector<WeakReference> SuspensionManager::_registeredFrames;

DependencyProperty^ SuspensionManager::FrameSessionStateKeyProperty =
	DependencyProperty::RegisterAttached("_FrameSessionStateKeyProperty",
	TypeName(String::typeid), TypeName(SuspensionManager::typeid), nullptr);

DependencyProperty^ SuspensionManager::FrameSessionStateProperty =
	DependencyProperty::RegisterAttached("_FrameSessionStateProperty",
	TypeName(IMap<String^, Object^>::typeid), TypeName(SuspensionManager::typeid), nullptr);

class ObjectSerializeHelper
{
public:
	// ����, ������������ ��� ������������� ��������������� �����
	enum StreamTypes {
		NullPtrType = 0,

		// �������������� ���� IPropertyValue
		UInt8Type, UInt16Type, UInt32Type, UInt64Type, Int16Type, Int32Type, Int64Type,
		SingleType, DoubleType, BooleanType, Char16Type, GuidType, StringType,

		// �������������� �������������� ����
		StringToObjectMapType,

		// �������� �������, ������������ ��� ����������� ����������� ������
		MapEndMarker
	};
	static String^ ReadString(DataReader^ reader);
	static IMap<String^, Object^>^ ReadStringToObjectMap(DataReader^ reader);
	static Object^ ReadObject(DataReader^ reader);
	static void WriteString(DataWriter^ writer, String^ string);
	static void WriteProperty(DataWriter^ writer, IPropertyValue^ propertyValue);
	static void WriteStringToObjectMap(DataWriter^ writer, IMap<String^, Object^>^ map);
	static void WriteObject(DataWriter^ writer, Object^ object);
};

/// <summary>
/// �������������� ������� � ����������� ��������� ������ ��� �������� ������. ��� ��������� �������������
/// ������� <see cref="SaveAsync"/> � ����������������� ������� <see cref="RestoreAsync"/>; ��� ����� ����������, ����� �������� ������������
/// ������ �� ��������� �����: ����������� ��������, ������� ����� �����, ����� � ��������� ������� ��������� � ������� ��������,
/// ����������� �������, ���������� ��������, ������ � �������������� GUID, ��� Map<String^, Object^>, ��� � ��������� �������������
/// ����������� �� �� �����������. ��������� ������ ������ ���� ����������� ����������.
/// </summary>
IMap<String^, Object^>^ SuspensionManager::SessionState()
{
	return _sessionState;
}

/// <summary>
/// ����������� ���������� <see cref="Frame"/>, ����� ���������� ���������� ��� ������� ��������� �
/// ������� <see cref="SessionState"/> � �������������� ������� �� ����� �������. ������ ������ ���������������� ���� ���
/// ����� ����� ��������, ���� ����������� �������� �� � ���������� ���������� ������. ���� ���
/// ����������� ��������� ��� ���������� ����� ��� ���� �������������,
/// ������ ��������� ���������� �����������������. ���������������� ������
/// <see cref="RestoreAsync(String)"/> �������� � �������������� ������� ���������.
/// </summary>
/// <param name="frame">���������, ������ ��������� �������� ������ ����������� �����������
/// <see cref="SuspensionManager"/></param>
/// <param name="sessionStateKey">���������� ���� � ������� <see cref="SessionState"/>, ������������ ���
/// �������� ������, ��������� � ����������.</param>
void SuspensionManager::RegisterFrame(Frame^ frame, String^ sessionStateKey)
{
	if (frame->GetValue(FrameSessionStateKeyProperty) != nullptr)
	{
		throw ref new FailureException("Frames can only be registered to one session state key");
	}

	if (frame->GetValue(FrameSessionStateProperty) != nullptr)
	{
		throw ref new FailureException("Frames must be either be registered before accessing frame session state, or not registered at all");
	}

	// �������� ������������ ������������ ��� ���������� ���������� ����� � ������� � ���������� ������ �������, ���������� ��������� �������
	// ���������� ���������
	frame->SetValue(FrameSessionStateKeyProperty, sessionStateKey);
	_registeredFrames.insert(_registeredFrames.begin(), WeakReference(frame));

	// ��������� ����������� �������������� ��������� ���������
	RestoreFrameNavigationState(frame);
}

/// <summary>
/// �������� ����� ������� <see cref="Frame"/>, ����� ������������������� � ������� <see cref="RegisterFrame"/>,
/// � �������� <see cref="SessionState"/>. ����� ����� ���������� ��������� ��������� �����
/// �������.
/// </summary>
/// <param name="frame">���������, ���������� �������� ��������� �������� ������ ����
/// ����������.</param>
void SuspensionManager::UnregisterFrame(Frame^ frame)
{
	// �������� ��������� ������ � �������� ������ �� ������ �������, ��������� ��������� �������
	// ��-�������� ����� ����������� (������ �� ������� ��������, ������� ���������� ���� ����������)
	auto key = safe_cast<String^>(frame->GetValue(FrameSessionStateKeyProperty));
	if (SessionState()->HasKey(key))
	{
		SessionState()->Remove(key);
	}
	_registeredFrames.erase(
		std::remove_if(_registeredFrames.begin(), _registeredFrames.end(), [=](WeakReference& e)
	{
		auto testFrame = e.Resolve<Frame>();
		return testFrame == nullptr || testFrame == frame;
	}),
		_registeredFrames.end()
		);
}

/// <summary>
/// ������������� ��������� ��� ��������� ������, ���������� � ��������� �������� <see cref="Frame"/>.
/// ��������� ������ �������, ����� ������������������ � ������� <see cref="RegisterFrame"/>,
/// ����������� � ����������������� ������������� � ������� ����������� �������
/// <see cref="SessionState"/>. �������������������� ������ ����� ���������� ���������,
/// �������, ��� �� �����, ����� ������������ ��� �������������� �������, ��������� ��
/// ���� ���������.
/// </summary>
/// <remarks>Apps may choose to rely on <see cref="NavigationHelper"/> to manage
/// ����������, ����������� � ��������, ������ ����������������� ��������� � ��������� ������ ������.</remarks>
/// <param name="frame">���������, ��� �������� ��������� ��������� ������.</param>
/// <returns>��������� ���������, � ������� ����������� ����� �� �������� ������������, ��� � �������
/// <see cref="SessionState"/>.</returns>
IMap<String^, Object^>^ SuspensionManager::SessionStateForFrame(Frame^ frame)
{
	auto frameState = safe_cast<IMap<String^, Object^>^>(frame->GetValue(FrameSessionStateProperty));

	if (frameState == nullptr)
	{
		auto frameSessionKey = safe_cast<String^>(frame->GetValue(FrameSessionStateKeyProperty));
		if (frameSessionKey != nullptr)
		{
			// ������������������ ������ �������� ��������������� ��������� ������
			if (!_sessionState->HasKey(frameSessionKey))
			{
				_sessionState->Insert(frameSessionKey, ref new Map<String^, Object^>());
			}
			frameState = safe_cast<IMap<String^, Object^>^>(_sessionState->Lookup(frameSessionKey));
		}
		else
		{
			// �������������������� ������ ����� ���������� ���������
			frameState = ref new Map<String^, Object^>();
		}
		frame->SetValue(FrameSessionStateProperty, frameState);
	}
	return frameState;
}

void SuspensionManager::RestoreFrameNavigationState(Frame^ frame)
{
	auto frameState = SessionStateForFrame(frame);
	if (frameState->HasKey("Navigation"))
	{
		frame->SetNavigationState(safe_cast<String^>(frameState->Lookup("Navigation")));
	}
}

void SuspensionManager::SaveFrameNavigationState(Frame^ frame)
{
	auto frameState = SessionStateForFrame(frame);
	frameState->Insert("Navigation", frame->GetNavigationState());
}

/// <summary>
/// ���������� �������� <see cref="SessionState"/>. ����� ���������� <see cref="Frame"/>,
/// ������������������ � ������� <see cref="RegisterFrame"/>, ����� �������� ���� �������
/// ���� ���������, �������, � ���� �������, ������������� �� �������� <see cref="Page"/> �����������
/// ���������� ������ ���������.
/// </summary>
/// <returns>����������� ������, ���������� ���������� ��������� ������.</returns>
task<void> SuspensionManager::SaveAsync(void)
{
	// ���������� ��������� ��������� ��� ���� ������������������ �������
	for (auto && weakFrame : _registeredFrames)
	{
		auto frame = weakFrame.Resolve<Frame>();
		if (frame != nullptr) SaveFrameNavigationState(frame);
	}

	// ���������� ������������ ��������� ������ � ����� ������� ������������ ������� � ������
	// ���������
	auto sessionData = ref new InMemoryRandomAccessStream();
	auto sessionDataWriter = ref new DataWriter(sessionData->GetOutputStreamAt(0));
	ObjectSerializeHelper::WriteObject(sessionDataWriter, _sessionState);

	// �������� ���������� ������ ��������� ������, ������� ����������� �������
	// ������ ���������� �� ����
	return task<unsigned int>(sessionDataWriter->StoreAsync()).then([=](unsigned int)
	{
		return sessionDataWriter->FlushAsync();
	})
		.then([=](bool flushSucceeded)
	{
		(void) flushSucceeded; // �������������� ��������
		return ApplicationData::Current->LocalFolder->CreateFileAsync(StringReference(sessionStateFilename),
			CreationCollisionOption::ReplaceExisting);
	})
		.then([=](StorageFile^ createdFile)
	{
		return createdFile->OpenAsync(FileAccessMode::ReadWrite);
	})
		.then([=](IRandomAccessStream^ newStream)
	{
		return RandomAccessStream::CopyAndCloseAsync(
			sessionData->GetInputStreamAt(0), newStream->GetOutputStreamAt(0));
	})
		.then([=](UINT64 copiedBytes)
	{
		(void) copiedBytes; // �������������� ��������
		return;
	});
}

/// <summary>
/// ��������������� ����� ����������� ������ <see cref="SessionState"/>. ����� ���������� <see cref="Frame"/>,
/// ������������������ � ������� <see cref="RegisterFrame"/>, ����� ����������� ���� ����������
/// ��������� ���������, �������, � ���� �������, ������������� �� �������� <see cref="Page"/> ����������� ��������������
/// ���������.
/// </summary>
/// <param name="version">������������� ������, ������� ������������ � ���������� ������, ����� ���������
/// ������ ������������� ������ ��������� ������ � ���� ����������. ����������� ���������
/// ������ ������ ����� ���������, ��� �������� � �������� ������� �������
/// <see cref="SessionState"/>.</param>
/// <returns>����������� ������, ���������� ������ ��������� ������. ����������
/// <see cref="SessionState"/> �� ������ ��������� �����������, ���� ��� ������ �� �����
/// ���������.</returns>
task<void> SuspensionManager::RestoreAsync(void)
{
	_sessionState->Clear();

	task<StorageFile^> getFileTask(ApplicationData::Current->LocalFolder->GetFileAsync(StringReference(sessionStateFilename)));
	return getFileTask.then([=](StorageFile^ stateFile)
	{
		task<BasicProperties^> getBasicPropertiesTask(stateFile->GetBasicPropertiesAsync());
		return getBasicPropertiesTask.then([=](BasicProperties^ stateFileProperties)
		{
			auto size = unsigned int(stateFileProperties->Size);
			if (size != stateFileProperties->Size) throw ref new FailureException("Session state larger than 4GB");
			task<IRandomAccessStreamWithContentType^> openReadTask(stateFile->OpenReadAsync());
			return openReadTask.then([=](IRandomAccessStreamWithContentType^ stateFileStream)
			{
				auto stateReader = ref new DataReader(stateFileStream);
				return task<unsigned int>(stateReader->LoadAsync(size)).then([=](unsigned int bytesRead)
				{
					(void) bytesRead; // �������������� ��������
					// �������������� ��������� ������
					Object^ content = ObjectSerializeHelper::ReadObject(stateReader);
					_sessionState = (Map<String^, Object^>^)content;

					// �������������� ���� ������������������ ������� � ������������ ���������
					for (auto && weakFrame : _registeredFrames)
					{
						auto frame = weakFrame.Resolve<Frame>();
						if (frame != nullptr)
						{
							frame->ClearValue(FrameSessionStateProperty);
							RestoreFrameNavigationState(frame);
						}
					}
				}, task_continuation_context::use_current());
			});
		});
	});
}

#pragma region Object serialization for a known set of types

void ObjectSerializeHelper::WriteString(DataWriter^ writer, String^ string)
{
	writer->WriteByte(StringType);
	writer->WriteUInt32(writer->MeasureString(string));
	writer->WriteString(string);
}

void ObjectSerializeHelper::WriteProperty(DataWriter^ writer, IPropertyValue^ propertyValue)
{
	switch (propertyValue->Type)
	{
	case PropertyType::UInt8:
		writer->WriteByte(StreamTypes::UInt8Type);
		writer->WriteByte(propertyValue->GetUInt8());
		return;
	case PropertyType::UInt16:
		writer->WriteByte(StreamTypes::UInt16Type);
		writer->WriteUInt16(propertyValue->GetUInt16());
		return;
	case PropertyType::UInt32:
		writer->WriteByte(StreamTypes::UInt32Type);
		writer->WriteUInt32(propertyValue->GetUInt32());
		return;
	case PropertyType::UInt64:
		writer->WriteByte(StreamTypes::UInt64Type);
		writer->WriteUInt64(propertyValue->GetUInt64());
		return;
	case PropertyType::Int16:
		writer->WriteByte(StreamTypes::Int16Type);
		writer->WriteUInt16(propertyValue->GetInt16());
		return;
	case PropertyType::Int32:
		writer->WriteByte(StreamTypes::Int32Type);
		writer->WriteUInt32(propertyValue->GetInt32());
		return;
	case PropertyType::Int64:
		writer->WriteByte(StreamTypes::Int64Type);
		writer->WriteUInt64(propertyValue->GetInt64());
		return;
	case PropertyType::Single:
		writer->WriteByte(StreamTypes::SingleType);
		writer->WriteSingle(propertyValue->GetSingle());
		return;
	case PropertyType::Double:
		writer->WriteByte(StreamTypes::DoubleType);
		writer->WriteDouble(propertyValue->GetDouble());
		return;
	case PropertyType::Boolean:
		writer->WriteByte(StreamTypes::BooleanType);
		writer->WriteBoolean(propertyValue->GetBoolean());
		return;
	case PropertyType::Char16:
		writer->WriteByte(StreamTypes::Char16Type);
		writer->WriteUInt16(propertyValue->GetChar16());
		return;
	case PropertyType::Guid:
		writer->WriteByte(StreamTypes::GuidType);
		writer->WriteGuid(propertyValue->GetGuid());
		return;
	case PropertyType::String:
		WriteString(writer, propertyValue->GetString());
		return;
	default:
		throw ref new InvalidArgumentException("Unsupported property type");
	}
}

void ObjectSerializeHelper::WriteStringToObjectMap(DataWriter^ writer, IMap<String^, Object^>^ map)
{
	writer->WriteByte(StringToObjectMapType);
	writer->WriteUInt32(map->Size);
	for (auto && pair : map)
	{
		WriteObject(writer, pair->Key);
		WriteObject(writer, pair->Value);
	}
	writer->WriteByte(MapEndMarker);
}

void ObjectSerializeHelper::WriteObject(DataWriter^ writer, Object^ object)
{
	if (object == nullptr)
	{
		writer->WriteByte(NullPtrType);
		return;
	}

	auto propertyObject = dynamic_cast<IPropertyValue^>(object);
	if (propertyObject != nullptr)
	{
		WriteProperty(writer, propertyObject);
		return;
	}

	auto mapObject = dynamic_cast<IMap<String^, Object^>^>(object);
	if (mapObject != nullptr)
	{
		WriteStringToObjectMap(writer, mapObject);
		return;
	}

	throw ref new InvalidArgumentException("Unsupported data type");
}

String^ ObjectSerializeHelper::ReadString(DataReader^ reader)
{
	int length = reader->ReadUInt32();
	String^ string = reader->ReadString(length);
	return string;
}

IMap<String^, Object^>^ ObjectSerializeHelper::ReadStringToObjectMap(DataReader^ reader)
{
	auto map = ref new Map<String^, Object^>();
	auto size = reader->ReadUInt32();
	for (unsigned int index = 0; index < size; index++)
	{
		auto key = safe_cast<String^>(ReadObject(reader));
		auto value = ReadObject(reader);
		map->Insert(key, value);
	}
	if (reader->ReadByte() != StreamTypes::MapEndMarker)
	{
		throw ref new InvalidArgumentException("Invalid stream");
	}
	return map;
}

Object^ ObjectSerializeHelper::ReadObject(DataReader^ reader)
{
	auto type = reader->ReadByte();
	switch (type)
	{
	case StreamTypes::NullPtrType:
		return nullptr;
	case StreamTypes::UInt8Type:
		return reader->ReadByte();
	case StreamTypes::UInt16Type:
		return reader->ReadUInt16();
	case StreamTypes::UInt32Type:
		return reader->ReadUInt32();
	case StreamTypes::UInt64Type:
		return reader->ReadUInt64();
	case StreamTypes::Int16Type:
		return reader->ReadInt16();
	case StreamTypes::Int32Type:
		return reader->ReadInt32();
	case StreamTypes::Int64Type:
		return reader->ReadInt64();
	case StreamTypes::SingleType:
		return reader->ReadSingle();
	case StreamTypes::DoubleType:
		return reader->ReadDouble();
	case StreamTypes::BooleanType:
		return reader->ReadBoolean();
	case StreamTypes::Char16Type:
		return (char16_t) reader->ReadUInt16();
	case StreamTypes::GuidType:
		return reader->ReadGuid();
	case StreamTypes::StringType:
		return ReadString(reader);
	case StreamTypes::StringToObjectMapType:
		return ReadStringToObjectMap(reader);
	default:
		throw ref new InvalidArgumentException("Unsupported property type");
	}
}

#pragma endregion
