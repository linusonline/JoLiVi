package se.lolektivet.jolivi;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import java.util.TimerTask;
import java.util.Timer;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.content.Context;
import android.view.MotionEvent;
import android.view.View;
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

class Heartbeat extends TimerTask
{
    private Timer mUpdateTimer;
    public static final float Fps = 20.0f;

    @Override
    public void run()
    {
        NativeFunctions.nativeHeartbeat();
    }

    public void start() {
        mUpdateTimer = new Timer();
        mUpdateTimer.schedule(this, 0, (int)(1000.0f / Fps));
    }
}

class DemoGLSurfaceView extends GLSurfaceView implements View.OnKeyListener
{
    private OrientationHandler mOrientationHandler;
    private DemoRenderer mRenderer;
    private static Heartbeat mHeartbeat;

    public DemoGLSurfaceView(Context context) {
        super(context);
        mRenderer = new DemoRenderer();
        setDebugFlags(DEBUG_CHECK_GL_ERROR | DEBUG_LOG_GL_CALLS);
        setRenderer(mRenderer);
        mOrientationHandler = new OrientationHandler(context);
        setFocusable(true);
        setFocusableInTouchMode(true);
        requestFocus();
    }

    public static void startHeartbeat()
    {
        mHeartbeat = new Heartbeat();
        mHeartbeat.start();
    }

    @Override
    public void onPause() {
        super.onPause();
        System.out.println("GLSurfaceView paused");
    }

    @Override
    public void onResume() {
        super.onResume();
        System.out.println("GLSurfaceView resumed");
    }

    public boolean onTouchEvent(final MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            System.out.println("Java received touch down event.");
            return NativeFunctions.nativeTouchDown();
        }
        if (event.getAction() == MotionEvent.ACTION_UP) {
            System.out.println("Java received touch up event.");
            return NativeFunctions.nativeTouchUp();
        }
        return false;
    }

    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        System.out.println("onKeyDown, keyCode: "+keyCode);
        if (NativeFunctions.nativeKeyDown(keyCode))
        {
            return true;
        }
        else
        {
            return super.onKeyDown(keyCode, event);
        }
    }
    public boolean onKeyUp(int keyCode, KeyEvent event)
    {
        System.out.println("onKeyUp, keyCode: "+keyCode);
        if (NativeFunctions.nativeKeyUp(keyCode))
        {
            return true;
        }
        else
        {
            return super.onKeyUp(keyCode, event);
        }
    }

    public boolean onKey(View v, int keyCode, KeyEvent event)
    {
        if (event.getAction() == KeyEvent.ACTION_DOWN) {
            System.out.println("onKeyDown, keyCode: "+keyCode);
            return NativeFunctions.nativeKeyDown(keyCode);
        }
        if (event.getAction() == KeyEvent.ACTION_UP) {
            System.out.println("onKeyUp, keyCode: "+keyCode);
            return NativeFunctions.nativeKeyUp(keyCode);
        }
        return false;
    }
}

class NativeFunctions
{
    public static native void nativeInit(float fps);
    public static native void nativeResize(int w, int h);
    public static native void nativeRender();
    public static native void nativeDone();
    public static native boolean nativeTouchDown();
    public static native boolean nativeTouchUp();
    public static native boolean nativeKeyDown(int keyCode);
    public static native boolean nativeKeyUp(int keyCode);
    public static native void nativeOrientationChange(int orientation);
    public static native void nativeHeartbeat();
}

class DemoRenderer implements GLSurfaceView.Renderer
{
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeFunctions.nativeInit(Heartbeat.Fps);
        DemoGLSurfaceView.startHeartbeat();
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
        NativeFunctions.nativeResize(w, h);
    }

    public void onDrawFrame(GL10 gl) {
        NativeFunctions.nativeRender();
    }
}
