package mooc.vandy.weatherserviceapp.services;

import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

import mooc.vandy.weatherserviceapp.WeatherCall;
import mooc.vandy.weatherserviceapp.WeatherData;

public class WeatherServiceSync extends LifecycleLoggingService
{
  private final WeatherCall.Stub mCallImpl = new WeatherCall.Stub()
  {
    @Override
    public List<WeatherData> getCurrentWeather(String location) throws RemoteException
    {
      List<WeatherData> results = WeatherServiceUtils.getResults(location);

      if (results != null)
      {
        Log.d(TAG, "" + results.size() + " results for location: " + location);
        return results;
      }
      else
      {
        return new ArrayList<WeatherData>();
      }
    }
  };

  public static Intent makeIntent(Context context)
  {
    return new Intent(context, WeatherServiceSync.class);
  }

  @Override
  public IBinder onBind(Intent intent)
  {
    super.onBind(intent);
    return mCallImpl;
  }
}
