package vandy.mooc.common;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;

public class GenericActivity<Interface, OpsType extends ConfigurableOps<Interface>> extends LifecycleLoggingActivity
{
  private final RetainedFragmentManager mRetainedFragmentManager = new RetainedFragmentManager(this.getFragmentManager(), TAG);
  private OpsType mOpsInstance;

  public void onCreate(Bundle savedInstanceState, Class<OpsType> opsType, Interface instance)
  {
    super.onCreate(savedInstanceState);

    try
    {
      handleConfiguration(opsType, instance);
    }
    catch (InstantiationException | IllegalAccessException e)
    {
      Log.d(TAG, "handleConfiguration " + e);
      throw new RuntimeException(e);
    }
  }

  public void handleConfiguration(Class<OpsType> opsType, Interface instance) throws InstantiationException, IllegalAccessException
  {
    if (mRetainedFragmentManager.firstTimeIn())
    {
      Log.d(TAG, "First time onCreate() call");
      initialize(opsType, instance);
    }
    else
    {
      Log.d(TAG, "Second or subsequent onCreate() call");

      mOpsInstance = mRetainedFragmentManager.get(opsType.getSimpleName());

      if (mOpsInstance == null)
        initialize(opsType, instance);
      else
        mOpsInstance.onConfiguration(instance, false);
    }
  }

  private void initialize(Class<OpsType> opsType, Interface instance) throws InstantiationException, IllegalAccessException
  {
    mOpsInstance = opsType.newInstance();

    mRetainedFragmentManager.put(opsType.getSimpleName(), mOpsInstance);
    mOpsInstance.onConfiguration(instance, true);
  }

  public OpsType getOps()
  {
    return mOpsInstance;
  }

  public RetainedFragmentManager getRetainedFragmentManager()
  {
    return mRetainedFragmentManager;
  }

  public Context getActivityContext()
  {
    return this;
  }

  public Context getApplicationContext()
  {
    return super.getApplicationContext();
  }
}
