package com.example.mysodemo;

import android.util.Log;

import org.json.JSONObject;

import java.lang.krom.IHook;

import top.canyie.pine.Pine;
import top.canyie.pine.PineConfig;
import top.canyie.pine.callback.MethodHook;

public class myModule implements IHook {
    public static String TAG="myModule";
    @Override
    public void onStart(Object app) {
        Log.i(TAG,"onStart my demo");
        PineConfig.debug = true; // 是否debug，true会输出较详细log
        PineConfig.debuggable = BuildConfig.DEBUG; // 该应用是否可调试，建议和配置文件中的值保持一致，否则会出现问题

        Log.i(TAG,"start Hook json");
        try {
            Pine.hook(JSONObject.class.getDeclaredMethod("toString"), new MethodHook() {
                @Override public void beforeCall(Pine.CallFrame callFrame) {
                    Log.i(TAG, "enter json toString");
                }

                @Override public void afterCall(Pine.CallFrame callFrame) {
                    Log.i(TAG, "leave json toString "+callFrame.getResult());
                }
            });
        } catch (NoSuchMethodException e) {
            throw new RuntimeException(e);
        }
    }
}
