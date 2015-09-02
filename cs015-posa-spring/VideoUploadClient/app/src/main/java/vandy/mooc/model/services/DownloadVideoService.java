package vandy.mooc.model.services;

import android.app.IntentService;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.support.v4.app.NotificationCompat.Builder;
import android.support.v4.content.LocalBroadcastManager;

import vandy.mooc.model.mediator.VideoDataMediator;

/**
 * Intent Service that runs in background and uploads the Video with a
 * given Id.  After the operation, it broadcasts the Intent to send
 * the result of the upload to the VideoListActivity.
 */
public class DownloadVideoService extends IntentService
{
  /**
   * Custom Action that will be used to send Broadcast to the
   * VideoListActivity.
   */
  public static final String ACTION_UPLOAD_SERVICE_RESPONSE = "vandy.mooc.services.UploadVideoService.RESPONSE";

  /**
   * It is used by Notification Manager to send Notifications.
   */
  private static final int NOTIFICATION_ID = 1;

  /**
   * VideoDataMediator mediates the communication between Video
   * Service and local storage in the Android device.
   */
  private VideoDataMediator mVideoMediator;

  /**
   * Manages the Notification displayed in System UI.
   */
  private NotificationManager mNotifyManager;

  /**
   * Builder used to build the Notification.
   */
  private Builder mBuilder;

  /**
   * Constructor for UploadVideoService.
   *
   * @param name
   */
  public DownloadVideoService(String name)
  {
    super("UploadVideoService");
  }

  /**
   * Constructor for UploadVideoService.
   */
  public DownloadVideoService()
  {
    super("UploadVideoService");
  }

  /**
   * Factory method that makes the explicit intent another Activity
   * uses to call this Service.
   *
   * @param context
   * @param videoUri
   * @return
   */
  public static Intent makeIntent(Context context, Uri videoUri)
  {
    return new Intent(context, DownloadVideoService.class).setData(videoUri);
  }

  /**
   * Hook method that is invoked on the worker thread with a request
   * to process. Only one Intent is processed at a time, but the
   * processing happens on a worker thread that runs independently
   * from other application logic.
   *
   * @param intent
   */
  @Override
  protected void onHandleIntent(Intent intent)
  {
    startNotification();

    mVideoMediator = new VideoDataMediator();
    finishNotification(mVideoMediator.uploadVideo(getApplicationContext(), intent.getData()));

    sendBroadcast();
  }

  /**
   * Send the Broadcast to Activity that the Video Upload is
   * completed.
   */
  private void sendBroadcast()
  {
    LocalBroadcastManager.getInstance(this)
      .sendBroadcast(new Intent(ACTION_UPLOAD_SERVICE_RESPONSE)
      .addCategory(Intent.CATEGORY_DEFAULT));
  }

  /**
   * Finish the Notification after the Video is Uploaded.
   *
   * @param status
   */
  private void finishNotification(String status)
  {
    mBuilder.setContentTitle(status).setProgress(0, 0, false)
      .setSmallIcon(android.R.drawable.stat_sys_upload_done)
      .setContentText("")
      .setTicker(status);

    mNotifyManager.notify(NOTIFICATION_ID, mBuilder.build());
  }

  /**
   * Starts the Notification to show the progress of video upload.
   */
  private void startNotification()
  {
    // Gets access to the Android Notification Service.
    mNotifyManager = (NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);

    // Create the Notification and set a progress indicator for an
    // operation of indeterminate length.
    mBuilder = newBuilder(this)
      .setContentTitle("Video Upload")
      .setContentText("Upload in progress")
      .setSmallIcon(android.R.drawable.stat_sys_upload)
      .setTicker("Uploading video")
      .setProgress(0, 0, true);

    // Build and issue the notification.
    mNotifyManager.notify(NOTIFICATION_ID, mBuilder.build());
  }
}
