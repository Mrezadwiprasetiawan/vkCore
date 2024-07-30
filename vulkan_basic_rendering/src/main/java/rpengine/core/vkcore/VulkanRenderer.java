package rpengine.core.vkcore;
import android.view.Surface;

public class VulkanRenderer {
  
  static{
		System.loadLibrary("vkcore");
	}
	
	private long handle;
	public VulkanRenderer(Surface surface){
		handle=Init(surface);
	}
	public static native long Init(Surface surface);
	public static native void CleanUp(long handle);
}
