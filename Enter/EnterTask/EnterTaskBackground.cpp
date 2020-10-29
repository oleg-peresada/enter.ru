#include "pch.h"
#include "EnterTaskBackground.h"
#include "TileNotificationTask.h"

using namespace EnterTask;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Background;
using namespace Windows::System::Threading;
using namespace Windows::UI::Notifications;

IVector<PromoBannerModels^>^ Promo = ref new Vector<PromoBannerModels^>();

EnterTaskBackground::EnterTaskBackground() : PeriodicTimer(nullptr), Defferal(nullptr)
{
}

EnterTaskBackground::~EnterTaskBackground()
{
	auto current_calendar = ref new Windows::Globalization::Calendar();
	current_calendar->AddDays(-1);
	CurrentTime = current_calendar->GetDateTime();
}

void EnterTaskBackground::Run(IBackgroundTaskInstance^ taskInstance)
{
	Defferal = taskInstance->GetDeferral();

	auto timerDelegate = [=](ThreadPoolTimer^ timer)
	{
		auto new_calendar = ref new Windows::Globalization::Calendar();

		auto current_calendar = ref new Windows::Globalization::Calendar();
		current_calendar->SetDateTime(CurrentTime);

		if (Promo->Size == 0 || new_calendar->Day != current_calendar->Day)
		{
			CurrentTime = new_calendar->GetDateTime();
			auto command = ref new PromoBannerCommands(14974, BannerType::Standart);
			auto operCommand = command->PromoBannerAsync(false);

			concurrency::create_task(operCommand).then([=](IVector<PromoBannerModels^>^ vectPromo)
			{
				Promo->Clear();
				Promo = ref new Vector<PromoBannerModels^>(begin(vectPromo), end(vectPromo));

				this->PushTile();
				this->Swap();
			});
		}
		else
		{
			this->PushTile();
			this->Swap();
		}
	};

	TimeSpan period;
	period.Duration = (1000 * 10000) * 60;
	PeriodicTimer = ThreadPoolTimer::CreatePeriodicTimer(ref new TimerElapsedHandler(timerDelegate), period);
}

void EnterTaskBackground::Swap()
{
	if (Promo == nullptr && Promo->Size == 0) return;

	auto firstElement = Promo->GetAt(0);
	std::vector<PromoBannerModels^> vect(begin(Promo), end(Promo));
	vect.erase(vect.begin());
	vect.push_back(firstElement);

	Promo->Clear();
	Promo = ref new Vector<PromoBannerModels^>(std::move(vect));
}

void EnterTaskBackground::PushTile()
{
	if (Promo == nullptr && Promo->Size == 0) return;

	auto element = Promo->First();
	auto name = element->Current->Name;
	auto id = element->Current->Id;

	auto tileUpdate = TileUpdateManager::CreateTileUpdaterForApplication();
	tileUpdate->EnableNotificationQueueForSquare150x150(true);
	tileUpdate->EnableNotificationQueueForWide310x150(true);

	auto tileXml = TileNotificationTask::TileWideText09("Акция", name);
	auto tileNotification = ref new TileNotification(tileXml);
	tileNotification->Tag = id;
	tileUpdate->Update(tileNotification);

	auto smallXml = TileNotificationTask::TileSquareText02("Акция", name);
	auto smalltileNotification = ref new TileNotification(smallXml);
	smalltileNotification->Tag = id;
	tileUpdate->Update(smalltileNotification);
}