#pragma once

using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace EnterTask
{
	class BannerSerializer
	{
	public:
		concurrency::task<void> Save(IVector<PromoBannerModels^>^ value);
		concurrency::task<IVector<PromoBannerModels^>^> Open();
	};
}