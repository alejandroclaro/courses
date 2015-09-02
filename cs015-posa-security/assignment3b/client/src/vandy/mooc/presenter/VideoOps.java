package vandy.mooc.presenter;

import java.lang.ref.WeakReference;
import java.util.List;

import vandy.mooc.common.ConfigurableOps;
import vandy.mooc.common.ContextView;
import vandy.mooc.common.GenericAsyncTask;
import vandy.mooc.common.GenericAsyncTaskOps;
import vandy.mooc.common.Utils;
import vandy.mooc.model.mediator.VideoDataMediator;
import vandy.mooc.model.mediator.webdata.Video;
import vandy.mooc.view.VideoListActivity;
import vandy.mooc.view.ui.VideoAdapter;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.net.Uri;
import android.os.StrictMode;
import android.util.Log;

public class VideoOps implements GenericAsyncTaskOps<Void, Void, List<Video>>, ConfigurableOps<VideoOps.View>
{
  private static final String TAG = VideoOps.class.getSimpleName();

  public interface View extends ContextView
  {
    void finish();
    void setAdapter(VideoAdapter videoAdapter);
    String getUser();
    String getPassword();
  }

  private WeakReference<VideoOps.View> mVideoView;
  private GenericAsyncTask<Void, Void, List<Video>, VideoOps> mAsyncTask;
  private VideoAdapter mAdapter;

  VideoDataMediator mVideoMediator;

  public VideoOps()
  {
  }

  public void onConfiguration(VideoOps.View view, boolean firstTimeIn)
  {
    final String time = firstTimeIn ? "first time" : "second+ time";

    Log.d(TAG, "onConfiguration() called the " + time + " with view = " + view);

    mVideoView = new WeakReference<VideoOps.View>(view);

    if (firstTimeIn)
    {
      StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
      StrictMode.setThreadPolicy(policy);

      mVideoMediator = new VideoDataMediator(mVideoView.get().getUser(), mVideoView.get().getPassword());
      mAdapter       = new VideoAdapter(mVideoView.get().getApplicationContext(), this);

      getVideoList();
    }

    mVideoView.get().setAdapter(mAdapter);
  }

  public void getVideoList()
  {
    mAsyncTask = new GenericAsyncTask<Void, Void, List<Video>, VideoOps>(this);
    mAsyncTask.execute();
  }

  @Override
  public List<Video> doInBackground(Void... params)
  {
    return mVideoMediator.getVideoList();
  }

  @Override
  public void onPostExecute(List<Video> videos)
  {
    displayVideoList(videos);
  }

  public void displayVideoList(List<Video> videos)
  {
    if (videos != null)
    {
      mAdapter.setVideos(videos);
      Utils.showToast(mVideoView.get().getActivityContext(), "Videos available from the Video Service");
    }
    else
    {
      Utils.showToast(mVideoView.get().getActivityContext(), "Please connect to the Video Service");
      mVideoView.get().finish();
    }
  }

  public void uploadVideo(Uri data)
  {
    mVideoMediator.uploadVideo(mVideoView.get().getApplicationContext(), data);
  }

  public void like(Video video)
  {
    mVideoMediator.like(video);
  }

  public void unlike(Video video)
  {
    mVideoMediator.unlike(video);
  }

  public List<String> getLikeBy(Video video)
  {
    return mVideoMediator.getLikeBy(video);
  }

  public boolean likeIt(Video video)
  {
    return getLikeBy(video).contains(mVideoView.get().getUser());
  }

  public void showUserWhoLikedVideo(int id)
  {
    Video        video = mAdapter.getItem(id);
    List<String> users = getLikeBy(video);

    AlertDialog.Builder builder = new AlertDialog.Builder(mVideoView.get().getActivityContext());

    builder.setTitle("Users who liked this video");
    builder.setItems(users.toArray(new CharSequence[users.size()]), new DialogInterface.OnClickListener()
    {
      public void onClick(DialogInterface dialog, int item)
      {
      }
    });

    AlertDialog alert = builder.create();
    alert.show();
  }
}
