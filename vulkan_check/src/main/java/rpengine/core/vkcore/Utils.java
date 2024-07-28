package rpengine.core.vkcore;

public class Utils {
  static{
    System.loadLibrary("vkcore");
  }
  public static native String Instance();
  public static native String API();
}
