package vandy.mooc.model.mediator;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import android.content.Context;
import android.net.Uri;
import android.util.Log;
import retrofit.RestAdapter.LogLevel;
import retrofit.client.OkClient;
import vandy.mooc.model.mediator.webdata.SecuredRestBuilder;
import vandy.mooc.model.mediator.webdata.UnsafeHttpsClient;
import vandy.mooc.model.mediator.webdata.Video;
import vandy.mooc.model.mediator.webdata.VideoServiceProxy;
import vandy.mooc.utils.Constants;
import vandy.mooc.utils.VideoMediaStoreUtils;

public class VideoDataMediator
{
  public static final String STATUS_UPLOAD_ERROR = "Upload failed";
  public static final String STATUS_UPLOAD_SUCCESSFUL = "Upload succeeded";

  private VideoServiceProxy mVideoServiceProxy;

  public VideoDataMediator(String userName, String password)
  {
    // Initialize the VideoServiceProxy.
    mVideoServiceProxy = new SecuredRestBuilder()
      .setLoginEndpoint(Constants.SERVER_URL + Constants.TOKEN_PATH)
      .setEndpoint(Constants.SERVER_URL)
      .setUsername(userName)
      .setPassword(password)
      .setClientId(Constants.CLIENT_ID)
      .setClient(new OkClient(UnsafeHttpsClient.getUnsafeOkHttpClient()))
      .setLogLevel(LogLevel.FULL)
      .build()
      .create(VideoServiceProxy.class);
  }

  public List<Video> getVideoList()
  {
    try
    {
      return (ArrayList<Video>) mVideoServiceProxy.getVideoList();
    }
    catch (Exception e)
    {
      return null;
    }
  }

  public String uploadVideo(Context context, Uri videoUri)
  {
    String filePath = VideoMediaStoreUtils.getPath(context, videoUri);
    Video androidVideo = VideoMediaStoreUtils.getVideo(context, filePath);

    if (androidVideo == null)
      return STATUS_UPLOAD_ERROR;

    try
    {
      Video receivedVideo = mVideoServiceProxy.addVideo(androidVideo);

      if (receivedVideo.getName() == androidVideo.getName())
        return STATUS_UPLOAD_SUCCESSFUL;
    }
    catch(Throwable e)
    {
      Log.d("MEDIATOR", e.getMessage());
    }

    return STATUS_UPLOAD_ERROR;
  }

  public void like(Video video)
  {
    try
    {
      mVideoServiceProxy.like(video.getId(), "");
    }
    catch (Throwable e)
    {
      throw e;
    }
  }

  public void unlike(Video video)
  {
    mVideoServiceProxy.unlike(video.getId(), "");
  }

  public List<String> getLikeBy(Video video)
  {
    return (ArrayList<String>) mVideoServiceProxy.getLikeBy(video.getId());
  }
}
