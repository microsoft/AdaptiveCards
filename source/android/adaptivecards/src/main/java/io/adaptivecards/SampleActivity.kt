package io.adaptivecards

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.ViewModelProvider
import io.adaptivecards.databinding.SampleBinding

class SampleActivity : AppCompatActivity() {

    //private val viewModel: SampleViewModel by viewModels { SampleViewModel.Factory }

    lateinit var viewModel: SampleViewModel

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        viewModel = ViewModelProvider(this)[SampleViewModel::class.java]
        val choices : MutableList<String> = ArrayList()
        choices.add("Dipesh")
        choices.add("Jain")
        viewModel.init(choices)
        val binding = SampleBinding.inflate(layoutInflater)
        binding.viewModel = viewModel
        setContentView(binding.root)

    }


//    override fun onCreateView(name: String, context: Context, attrs: AttributeSet): View? {
//        val view: View? = super.onCreateView(name, context, attrs)
//        val binding = SampleBinding.inflate(layoutInflater)
//        binding.viewModel = viewModel
//        return view
//    }
}