package rpengine.core.vkcore;

public class Vulkan {
  static{
		System.loadLibrary("vkcore");
	}
	public static native void Init();
	public static native void PickPhysicalDevice(int index);
	public static native void CleanUp();
}
