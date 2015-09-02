package vandy.mooc.view;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.inputmethod.EditorInfo;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import vandy.mooc.R;
import vandy.mooc.common.GenericActivity;
import vandy.mooc.presenter.LoginOps;

public class LoginActivity extends GenericActivity<LoginOps.View, LoginOps> implements LoginOps.View
{
  private AutoCompleteTextView mUserView;
  private EditText mPasswordView;

  @Override
  protected void onCreate(Bundle savedInstanceState)
  {
    setContentView(R.layout.activity_login);

    mUserView = (AutoCompleteTextView)findViewById(R.id.user);

    mPasswordView = (EditText) findViewById(R.id.password);
    mPasswordView.setOnEditorActionListener(new TextView.OnEditorActionListener()
    {
      @Override
      public boolean onEditorAction(TextView textView, int id, KeyEvent keyEvent)
      {
        if (id == R.id.login || id == EditorInfo.IME_NULL)
        {
          attemptLogin();
          return true;
        }

        return false;
      }
    });

    Button mSignInButton = (Button) findViewById(R.id.sign_in_button);
    mSignInButton.setOnClickListener(new OnClickListener()
    {
      @Override
      public void onClick(View view)
      {
        attemptLogin();
      }
    });

    super.onCreate(savedInstanceState, LoginOps.class, this);
  }

  public void attemptLogin()
  {
    mUserView.setError(null);
    mPasswordView.setError(null);

    String user     = mUserView.getText().toString();
    String password = mPasswordView.getText().toString();

    boolean cancel = false;
    View focusView = null;

    if (TextUtils.isEmpty(password))
    {
      mPasswordView.setError(getString(R.string.error_field_required));
      focusView = mPasswordView;
      cancel = true;
    }

    if (TextUtils.isEmpty(user))
    {
      mUserView.setError(getString(R.string.error_field_required));
      focusView = mUserView;
      cancel = true;
    }

    if (cancel)
    {
      focusView.requestFocus();
    }
    else
    {
      Intent intent = new Intent(this, VideoListActivity.class);
      intent.putExtra(VideoListActivity.USER_NAME, user);
      intent.putExtra(VideoListActivity.PASSWORD, password);

      startActivity(intent);
    }
  }
}
