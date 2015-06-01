package mooc.vandy.weatherserviceapp.operations;

import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Handler;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import java.lang.ref.WeakReference;
import java.util.List;

import mooc.vandy.weatherserviceapp.R;
import mooc.vandy.weatherserviceapp.WeatherCall;
import mooc.vandy.weatherserviceapp.WeatherData;
import mooc.vandy.weatherserviceapp.WeatherRequest;
import mooc.vandy.weatherserviceapp.WeatherResults;
import mooc.vandy.weatherserviceapp.activities.DisplayWeatherActivity;
import mooc.vandy.weatherserviceapp.activities.MainActivity;
import mooc.vandy.weatherserviceapp.services.WeatherServiceAsync;
import mooc.vandy.weatherserviceapp.services.WeatherServiceSync;

public class WeatherOpsImpl implements WeatherOps
{
  protected final String TAG = getClass().getSimpleName();

  protected WeakReference<MainActivity>            mActivity;
  protected WeakReference<EditText>                mEditText;
  private GenericServiceConnection<WeatherCall>    mServiceConnectionSync;
  private GenericServiceConnection<WeatherRequest> mServiceConnectionAsync;

  private final Handler             mDisplayHandler = new Handler();
  private final WeatherResults.Stub mAcronymResults = new WeatherResults.Stub()
  {
    @Override
    public void sendResults(final List<WeatherData> results) throws RemoteException
    {
      mDisplayHandler.post(new Runnable()
      {
        public void run()
        {
          displayResults(results);
        }
      });
    }
  };

  public WeatherOpsImpl(MainActivity activity)
  {
    mActivity = new WeakReference<>(activity);

    initialize();

    mServiceConnectionSync  = new GenericServiceConnection<>(WeatherCall.class);
    mServiceConnectionAsync = new GenericServiceConnection<>(WeatherRequest.class);
  }

  @Override
  public void bindService()
  {
    Log.d(TAG, "calling bindService()");

    if (mServiceConnectionSync.getInterface() == null)
    {
      mActivity.get().bindService(
        WeatherServiceSync.makeIntent(mActivity.get()),
        mServiceConnectionSync,
        Context.BIND_AUTO_CREATE);
    }

    if (mServiceConnectionAsync.getInterface() == null)
    {
      mActivity.get().bindService(
        WeatherServiceAsync.makeIntent(mActivity.get()),
        mServiceConnectionAsync,
        Context.BIND_AUTO_CREATE);
    }
  }

  @Override
  public void unbindService()
  {
    if (mActivity.get().isChangingConfigurations())
    {
      Log.d(TAG, "just a configuration change - unbindService() not called");
      return;
    }

    Log.d(TAG, "calling unbindService()");

    if (mServiceConnectionAsync.getInterface() != null)
      mActivity.get().getApplicationContext().unbindService(mServiceConnectionAsync);

    if (mServiceConnectionSync.getInterface() != null)
      mActivity.get().getApplicationContext().unbindService(mServiceConnectionSync);
  }

  @Override
  public void onConfigurationChange(MainActivity activity)
  {
    Log.d(TAG, "onConfigurationChange() called");

    mActivity = new WeakReference<>(activity);
    initialize();
  }

  public void onGetSyncClick(View view)
  {
    final WeatherCall call    = mServiceConnectionSync.getInterface();
    final String      location = mEditText.get().getText().toString();

    if (call == null)
    {
      Log.d(TAG, "WeatherCall was null.");
      return;
    }

    new AsyncTask<String, Void, List<WeatherData>>()
    {
      private String mLocation;

      protected List<WeatherData> doInBackground(String... location)
      {
        try
        {
          mLocation = location[0];
          return call.getCurrentWeather(mLocation);
        }
        catch (RemoteException e)
        {
          e.printStackTrace();
        }

        return null;
      }

      protected void onPostExecute(List<WeatherData> results)
      {
        displayResults(results);
      }
    }.execute(location);
  }

  public void onGetAsyncClick(View view)
  {
    final WeatherRequest request = mServiceConnectionAsync.getInterface();

    if (request == null)
    {
      Log.d(TAG, "WeatherRequest was null.");
      return;
    }

    try
    {
      final String location = mEditText.get().getText().toString();

      request.getCurrentWeather(location, mAcronymResults);
    }
    catch (RemoteException e)
    {
      Log.e(TAG, "RemoteException:" + e.getMessage());
    }
  }

  private void initialize()
  {
    mActivity.get().setContentView(R.layout.activity_main);
    mEditText = new WeakReference<>((EditText)mActivity.get().findViewById(R.id.locationText));
  }

  private void displayResults(List<WeatherData> results)
  {
    if (results.size() == 0)
    {
      Toast.makeText(mActivity.get(), "No weather data for the provided location found.", Toast.LENGTH_SHORT).show();
      return;
    }

    Intent intent = DisplayWeatherActivity.makeIntent(mActivity.get(), results.get(0));
    mActivity.get().startActivity(intent);
  }
}
