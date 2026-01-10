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

			device = deviceCreator.create();
			device.powerOn();

			DeviceTester deviceTester;

			deviceTester.test(device);
		}

	private:
		Device device;
	};

	void run()
	{
		DeviceManager deviceManager;

		deviceManager.registerDevice();
	}
}
