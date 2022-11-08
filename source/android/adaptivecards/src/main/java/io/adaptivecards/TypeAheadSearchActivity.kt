package io.adaptivecards

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.ViewModelProvider
import io.adaptivecards.databinding.ActivityTypeAheadSearchBinding

class TypeAheadSearchActivity : AppCompatActivity() {
    lateinit var viewModel: TypeAheadSearchViewModel

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        viewModel = ViewModelProvider(this)[TypeAheadSearchViewModel::class.java]
        val choices : MutableList<String> = ArrayList()
        choices.add("Dipesh")
        choices.add("Jain")
        viewModel.init(choices)
        val binding = ActivityTypeAheadSearchBinding.inflate(layoutInflater)
        binding.viewModel = viewModel
        setContentView(binding.root)
    }
}