package claro.alejandro.modernartui;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ImageView;
import android.widget.SeekBar;

public class MainActivity extends ActionBarActivity
{
  private static final String TAG       = "modernartui";
  private static final int RECTANGLES_COUNT = 5;

  int[]       mColors = { 0xff7a98e6, 0xffff68d9, 0xffb30018, 0xffffffff, 0xff001f99 };
  ImageView[] mRectangles;

  @Override
  protected void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);

    mRectangles = new ImageView[RECTANGLES_COUNT];
    mRectangles[0] = (ImageView)findViewById(R.id.rectangle_lt);
    mRectangles[1] = (ImageView)findViewById(R.id.rectangle_lb);
    mRectangles[2] = (ImageView)findViewById(R.id.rectangle_rt);
    mRectangles[3] = (ImageView)findViewById(R.id.rectangle_rm);
    mRectangles[4] = (ImageView)findViewById(R.id.rectangle_rb);

    updateUI(0);

    SeekBar bar = (SeekBar)findViewById(R.id.seek_bar);
    bar.setMax(180);

    bar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener()
    {
      @Override
      public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser)
      {
        updateUI(progress);
      }

      @Override
      public void onStartTrackingTouch(SeekBar seekBar)
      {
      }

      @Override
      public void onStopTrackingTouch(SeekBar seekBar)
      {
      }
    });
  }

  @Override
  public boolean onCreateOptionsMenu(Menu menu)
  {
    getMenuInflater().inflate(R.menu.menu_main, menu);
    return true;
  }

  @Override
  public boolean onOptionsItemSelected(MenuItem item)
  {
    int id = item.getItemId();

    if (id == R.id.more_information)
    {
      showMoreInformationDialog();
      return true;
    }

    return super.onOptionsItemSelected(item);
  }

  private void showMoreInformationDialog()
  {
    AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);

    builder.setTitle("Inspired by the works of artists such as Piet Mondrian.");
    builder.setMessage("Click below to learn more!");

    builder.setNegativeButton("Not Now", new DialogInterface.OnClickListener()
    {
      public void onClick(DialogInterface dialog, int id)
      {
        dialog.cancel();
      }
    });

    builder.setPositiveButton("Visit MOMA", new DialogInterface.OnClickListener()
    {
      public void onClick(DialogInterface dialog, int id)
      {
        showMomaWebsite();
      }
    });

    AlertDialog dialog = builder.create();
    dialog.show();
  }

  private void showMomaWebsite()
  {
    Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse("http://www.moma.org/"));
    startActivity(intent);
  }

  private void updateUI(int value)
  {
    float[] hsv = new float[3];

    Log.d(TAG, "updateUI: " + value);

    for (int i = 0; i < mRectangles.length; ++i)
    {
      Color.colorToHSV(mColors[i % mColors.length], hsv);
      hsv[0] = (hsv[0] + value) % 360.0f;

      mRectangles[i].setImageDrawable(new ColorDrawable(Color.HSVToColor(hsv)));
    }
  }
}
