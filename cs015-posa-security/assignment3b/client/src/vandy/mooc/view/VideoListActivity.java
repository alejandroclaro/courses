package vandy.mooc.view;

import vandy.mooc.R;
import vandy.mooc.common.GenericActivity;
import vandy.mooc.common.Utils;
import vandy.mooc.presenter.VideoOps;
import vandy.mooc.view.ui.FloatingActionButton;
import vandy.mooc.view.ui.VideoAdapter;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;

public class VideoListActivity extends GenericActivity<VideoOps.View, VideoOps>implements VideoOps.View
{
  public final static String USER_NAME = "user";
  public final static String PASSWORD = "password";

  private final int REQUEST_GET_VIDEO = 1;
  private FloatingActionButton mUploadVideoButton;
  private ListView mVideosList;

  @Override
  protected void onCreate(Bundle savedInstanceState)
  {
    setContentView(R.layout.video_list_activity);

    mVideosList = (ListView) findViewById(R.id.videoList);
    mUploadVideoButton = (FloatingActionButton) findViewById(R.id.fabButton);

    mUploadVideoButton.setOnClickListener(new OnClickListener()
    {
      public void onClick(View v)
      {
        displayChooserDialog();
      }
    });

    mVideosList.setOnItemClickListener(new OnItemClickListener()
    {
      @Override
      public void onItemClick(AdapterView<?> parent, View view, int position, long id)
      {
        getOps().showUserWhoLikedVideo(position);
      }
    });

    super.onCreate(savedInstanceState, VideoOps.class, this);
  }

  private void displayChooserDialog()
  {
    final Intent videoGalleryIntent = new Intent(Intent.ACTION_GET_CONTENT).setType("video/*")
        .putExtra(Intent.EXTRA_LOCAL_ONLY, true);

    final Intent recordVideoIntent = new Intent(MediaStore.ACTION_VIDEO_CAPTURE);
    final Intent chooserIntent = Intent.createChooser(videoGalleryIntent, "Upload Video via");

    chooserIntent.putExtra(Intent.EXTRA_INITIAL_INTENTS, new Intent[] { recordVideoIntent });

    startActivityForResult(chooserIntent, REQUEST_GET_VIDEO);

  }

  @Override
  public void onActivityResult(int requestCode, int resultCode, Intent data)
  {
    if (requestCode == REQUEST_GET_VIDEO)
    {
      if (resultCode == Activity.RESULT_OK)
      {
        Utils.showToast(this, "Uploading video");
        getOps().uploadVideo(data.getData());
        getOps().getVideoList();
      }
      else
      {
        Utils.showToast(this, "Could not get video to upload");
      }
    }
  }

  @Override
  protected void onResume()
  {
    super.onResume();
  }

  @Override
  protected void onPause()
  {
    super.onPause();
  }

  @Override
  public void setAdapter(VideoAdapter videoAdapter)
  {
    mVideosList.setAdapter(videoAdapter);
  }

  @Override
  public void finish()
  {
    super.finish();
  }

  @Override
  public String getUser()
  {
    return getIntent().getStringExtra(USER_NAME);
  }

  @Override
  public String getPassword()
  {
    return getIntent().getStringExtra(PASSWORD);
  }

  @Override
  public boolean onCreateOptionsMenu(Menu menu)
  {
    return true;
  }
}
