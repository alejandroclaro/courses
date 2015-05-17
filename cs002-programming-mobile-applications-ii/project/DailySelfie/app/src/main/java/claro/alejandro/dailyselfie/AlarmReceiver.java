package claro.alejandro.dailyselfie;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class AlarmReceiver extends BroadcastReceiver
{
  @Override
  public void onReceive(Context context, Intent intent)
  {
    NotificationManager notificationManager = (NotificationManager)context.getSystemService(Context.NOTIFICATION_SERVICE);

    Intent activityIntent = new Intent(context, MainActivity.class);
    activityIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);

    PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, activityIntent, 0);

    Notification notification = new Notification.Builder(context)
      .setContentTitle(context.getString(R.string.app_name))
      .setContentText(context.getString(R.string.alarm_message))
      .setSmallIcon(android.R.drawable.ic_menu_camera)
      .setContentIntent(pendingIntent)
      .build();

    notification.flags |= Notification.FLAG_AUTO_CANCEL;
    notificationManager.notify(0, notification);
  }
}
