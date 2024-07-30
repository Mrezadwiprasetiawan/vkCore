package rpengine.core.vkcore;

import android.content.Context;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.ViewGroup;

public class VkSurfaceView extends SurfaceView {
    private Renderer renderer;
    private Handler backgroundHandler;
    private HandlerThread handlerThread;
    private Runnable renderTask;
    private boolean running;

    public VkSurfaceView(Context context) {
        super(context);
        setLayoutParams(new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        initializeRendering();
    }

    private void initializeRendering() {
        handlerThread = new HandlerThread("RenderingThread");
        handlerThread.start();
        backgroundHandler = new Handler(handlerThread.getLooper());

        renderTask = new Runnable() {
            @Override
            public void run() {
                if (renderer != null) {
                    renderer.onDrawFrame();
                }
                // Immediately reschedule the task to run again
                backgroundHandler.post(this);
            }
        };
    }

    public void setRenderer(Renderer renderer) {
        this.renderer = renderer;
        if (renderer != null) {
            running = true;
            backgroundHandler.post(renderTask); // Start rendering in the background
        }
    }

    @Override
    protected void onDetachedFromWindow() {
        super.onDetachedFromWindow();
        if (running) {
            backgroundHandler.removeCallbacks(renderTask); // Stop the rendering task
            if (renderer != null) {
                renderer.CleanUp();
            }
            handlerThread.quitSafely(); // Quit the background thread
            running = false;
        }
    }

    public class Renderer {
        static {
            System.loadLibrary("vkcore");
        }

        private long handle;

        public Renderer(VkSurfaceView vkSurfaceView) {
            handle = Init(vkSurfaceView.getHolder().getSurface());
        }

        public native long Init(Surface surface);
        public native void CleanUp();
        public native void onDrawFrame();
    }
}