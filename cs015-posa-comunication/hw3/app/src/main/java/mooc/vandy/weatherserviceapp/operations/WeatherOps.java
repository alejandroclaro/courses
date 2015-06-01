package mooc.vandy.weatherserviceapp.operations;

import android.view.View;

import mooc.vandy.weatherserviceapp.activities.MainActivity;

public interface WeatherOps
{
  public void bindService();
  public void unbindService();
  public void onConfigurationChange(MainActivity activity);
  public void onGetSyncClick(View view);
  public void onGetAsyncClick(View view);
}
