package mooc.vandy.weatherserviceapp.activities;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import mooc.vandy.weatherserviceapp.operations.WeatherOps;
import mooc.vandy.weatherserviceapp.operations.WeatherOpsImpl;

public class MainActivity extends LifecycleLoggingActivity
{
  private final RetainedFragmentManager mRetainedFragmentManager = new RetainedFragmentManager(
    this.getFragmentManager(),
    TAG);

  private WeatherOps mOps = null;

  public void onGetSyncClick(View view)
  {
    mOps.onGetSyncClick(view);
  }

  public void onGetAsyncClick(View view)
  {
    mOps.onGetAsyncClick(view);
  }

  @Override
  protected void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);

    handleConfigurationChanges();
  }

  private void handleConfigurationChanges()
  {
    if (mRetainedFragmentManager.firstTimeIn())
    {
      Log.d(TAG, "First time onCreate() call");

      mOps = new WeatherOpsImpl(this);

      mRetainedFragmentManager.put("OPS_STATE", mOps);
      mOps.bindService();
    }
    else
    {
      Log.d(TAG, "Second or subsequent onCreate() call");

      mOps = mRetainedFragmentManager.get("OPS_STATE");

      if (mOps == null)
      {
        mOps = new WeatherOpsImpl(this);

        mRetainedFragmentManager.put("OPS_STATE", mOps);
        mOps.bindService();
      }
      else
      {
        mOps.onConfigurationChange(this);
      }
    }
  }
}
