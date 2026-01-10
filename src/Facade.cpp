export module DemoFacade;

export namespace DemoFacade
{
	class Device
	{
	public:
		void powerOn()
		{
		}
	};

	class DeviceCreator
	{
	public:
		Device create()
		{
			return Device();
		}
	};

	class DeviceTester
	{
	public:
		void test(const Device& device)
		{
		}
	};

	class DeviceManager
	{
	public:
		void registerDevice()
		{
			DeviceCreator deviceCreator;

			mDevice = deviceCreator.create();
			mDevice.powerOn();

			DeviceTester deviceTester;

			deviceTester.test(mDevice);
		}

	private:
		Device mDevice;
	};

	void run()
	{
		DeviceManager deviceManager;

		deviceManager.registerDevice();
	}
}
