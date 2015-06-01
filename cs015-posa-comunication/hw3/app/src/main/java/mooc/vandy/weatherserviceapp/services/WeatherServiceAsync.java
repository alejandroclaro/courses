package mooc.vandy.weatherserviceapp.services;

import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

import mooc.vandy.weatherserviceapp.WeatherData;
import mooc.vandy.weatherserviceapp.WeatherRequest;
import mooc.vandy.weatherserviceapp.WeatherResults;

public class WeatherServiceAsync extends LifecycleLoggingService
{
  private final WeatherRequest.Stub mRequestImpl = new WeatherRequest.Stub()
  {
    @Override
    public void getCurrentWeather(String location, WeatherResults callback) throws RemoteException
    {
      final List<WeatherData> results = WeatherServiceUtils.getResults(location);

      if (results != null)
      {
        Log.d(TAG, "" + results.size() + " results for location: " + location);
        callback.sendResults(results);
      }
      else
      {
        Log.d(TAG, "No results for location: " + location + "found.");
        callback.sendResults(new ArrayList<WeatherData>());
      }
    }
  };

  public static Intent makeIntent(Context context)
  {
    return new Intent(context, WeatherServiceAsync.class);
  }

  @Override
  public IBinder onBind(Intent intent)
  {
    super.onBind(intent);
    return mRequestImpl;
  }
}
