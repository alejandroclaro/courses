package mooc.vandy.weatherserviceapp.activities;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import mooc.vandy.weatherserviceapp.R;
import mooc.vandy.weatherserviceapp.WeatherData;

public class DisplayWeatherActivity extends LifecycleLoggingActivity
{
  private final static String WEATHER_DATA = "WEATHER_DATA";

  static public Intent makeIntent(Context context, WeatherData data)
  {
    Intent result = new Intent(context, DisplayWeatherActivity.class);

    result.putExtra(WEATHER_DATA, data);
    return result;
  }

  @Override
  protected void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);

    setContentView(R.layout.activity_display_weather);

    WeatherData data = getIntent().getParcelableExtra(WEATHER_DATA);

    setValue(R.id.nameView,     data.getName());
    setValue(R.id.speedView,    Double.toString(data.getSpeed()));
    setValue(R.id.degView,      Double.toString(data.getDeg()));
    setValue(R.id.tempView,     Double.toString(data.getTemp()));
    setValue(R.id.humidityView, Double.toString(data.getHumidity()));
    setValue(R.id.sunriseView,  Long.toString(data.getSunrise()));
    setValue(R.id.sunsetView,   Long.toString(data.getSunset()));
  }

  private void setValue(int id, String value)
  {
    TextView view = (TextView)findViewById(id);
    view.setText(value);
  }
}
