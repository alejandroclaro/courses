package claro.alejandro.dailyselfie;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.provider.MediaStore;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class MainActivity extends ActionBarActivity
{
  static final int  REQUEST_IMAGE_CAPTURE = 1;
  static final long TWO_MINUTES           = 120 * 1000L;

  private SelfieViewAdapter mAdapter;

  @Override
  protected void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main_activity);

    mAdapter = new SelfieViewAdapter(this);

    ListView listView = (ListView)findViewById(R.id.selfie_thumbs);
    listView.setAdapter(mAdapter);

    listView.setOnItemClickListener(new AdapterView.OnItemClickListener()
    {
      @Override
      public void onItemClick(AdapterView parent, View view, int position, long id)
      {
        showSefie(position);
      }
    });

    mAdapter.load();
    setAlarm();
  }

  @Override
  public boolean onCreateOptionsMenu(Menu menu)
  {
    // Inflate the menu; this adds items to the action bar if it is present.
    getMenuInflater().inflate(R.menu.menu_main, menu);
    return true;
  }

  @Override
  public boolean onOptionsItemSelected(MenuItem item)
  {
    // Handle action bar item clicks here. The action bar will
    // automatically handle clicks on the Home/Up button, so long
    // as you specify a parent activity in AndroidManifest.xml.
    int id = item.getItemId();

    switch (id)
    {
      case R.id.action_camera:
        showFrontCameraPicture();
        return true;
      case R.id.action_clear:
        mAdapter.clear();
        return true;
      default:
        return super.onOptionsItemSelected(item);
    }
  }

  @Override
  protected void onActivityResult(int requestCode, int resultCode, Intent data)
  {
    if (requestCode == REQUEST_IMAGE_CAPTURE && resultCode == RESULT_OK)
    {
      Bundle       extras       = data.getExtras();
      SelfieRecord selfieRecord = new SelfieRecord(generateNewTitle(), (Bitmap)extras.get("data"));

      mAdapter.add(selfieRecord);
    }
  }

  private void showFrontCameraPicture()
  {
    Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
    //intent.putExtra("android.intent.extras.CAMERA_FACING", 1);

    if (intent.resolveActivity(getPackageManager()) != null)
    {
      startActivityForResult(intent, REQUEST_IMAGE_CAPTURE);
    }
  }

  private void showSefie(int position)
  {
    Intent intent = new Intent(Intent.ACTION_VIEW);

    intent.setDataAndType(mAdapter.getItem(position).getImageUri(), "image/png");

    startActivity(intent);
  }

  private String generateNewTitle()
  {
    DateFormat dateFormat = new SimpleDateFormat("yyyyMMdd_HHmmss");
    Date date = new Date();

    return dateFormat.format(date);
  }

  private void setAlarm()
  {
    Intent        alarmIntent = new Intent(this, AlarmReceiver.class);
    PendingIntent intent      = PendingIntent.getBroadcast(this, 0, alarmIntent, 0);

    AlarmManager manager = (AlarmManager)getSystemService(Context.ALARM_SERVICE);
    manager.setRepeating(AlarmManager.RTC_WAKEUP, System.currentTimeMillis() + TWO_MINUTES, TWO_MINUTES, intent);
  }
}
