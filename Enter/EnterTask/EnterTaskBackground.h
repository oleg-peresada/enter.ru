#pragma once

using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Background;
using namespace Windows::System::Threading;

namespace EnterTask
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class EnterTaskBackground sealed : public IBackgroundTask
	{
	public:
		EnterTaskBackground();
		virtual ~EnterTaskBackground();
		virtual void Run(IBackgroundTaskInstance^ taskInstance);
	private:
		void Swap();
		void PushTile();
		ThreadPoolTimer^ PeriodicTimer;
		DateTime CurrentTime;
		Agile<BackgroundTaskDeferral^> Defferal;
	};
}