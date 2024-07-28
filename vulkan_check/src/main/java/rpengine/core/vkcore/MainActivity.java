package rpengine.core.vkcore;

import android.app.Activity;
import android.os.Bundle;
import rpengine.core.vkcore.databinding.ActivityMainBinding;

public class MainActivity extends Activity {

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
		binding.text.setText(Utils.Instance()+"\n"+Utils.API());
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        this.binding = null;
    }
}
