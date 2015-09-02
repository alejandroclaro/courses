package vandy.mooc.presenter;

import vandy.mooc.common.ConfigurableOps;
import vandy.mooc.common.ContextView;

public class LoginOps implements ConfigurableOps<LoginOps.View>
{
  public interface View extends ContextView
  {
  }

  public LoginOps()
  {
  }

  @Override
  public void onConfiguration(View view, boolean firstTimeIn)
  {
  }
}
