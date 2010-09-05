package se.lolektivet.jolivi;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.content.Context;
import android.view.MotionEvent;
import android.view.OrientationEventListener;
import android.view.KeyEvent;
import android.os.Bundle;

public class JoLiViActivity extends Activity
{
    private GLSurfaceView mGLView;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        mGLView = new DemoGLSurfaceView(this);
        setContentView(mGLView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mGLView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }

    static {
        System.loadLibrary("jolivi");
    }
}

class OrientationHandler extends OrientationEventListener
{
    public OrientationHandler(Context context)
    {
        super(context);
        if (canDetectOrientation())
        {
            enable();
        }
    }

    public void onOrientationChanged(int orientation)
    {
        NativeFunctions.nativeOrientationChange(orientation);
    }
}

class DemoGLSurfaceView extends GLSurfaceView {
    private OrientationHandler mOrientationHandler;

    public DemoGLSurfaceView(Context context) {
        super(context);
        mRenderer = new DemoRenderer();
        setRenderer(mRenderer);
        mOrientationHandler = new OrientationHandler(context);
    }

    public boolean onTouchEvent(final MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            return NativeFunctions.nativeTouchDown();
        }
        if (event.getAction() == MotionEvent.ACTION_UP) {
            return NativeFunctions.nativeTouchUp();
        }
        return false;
    }

    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        return NativeFunctions.nativeKeyDown(keyCode);
    }

    public boolean onKeyUp(int keyCode, KeyEvent event)
    {
        return NativeFunctions.nativeKeyUp(keyCode);
    }

    DemoRenderer mRenderer;
}

class NativeFunctions
{
    public static native void nativeInit();
    public static native void nativeResize(int w, int h);
    public static native void nativeRender();
    public static native void nativeDone();
    public static native boolean nativeTouchDown();
    public static native boolean nativeTouchUp();
    public static native boolean nativeKeyDown(int keyCode);
    public static native boolean nativeKeyUp(int keyCode);
    public static native void nativeOrientationChange(int orientation);
}

class DemoRenderer implements GLSurfaceView.Renderer {
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeFunctions.nativeInit();
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
        NativeFunctions.nativeResize(w, h);
    }

    public void onDrawFrame(GL10 gl) {
        NativeFunctions.nativeRender();
    }
}
