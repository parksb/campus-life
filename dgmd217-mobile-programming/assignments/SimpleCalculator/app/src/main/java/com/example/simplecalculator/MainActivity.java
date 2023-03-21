package com.example.simplecalculator;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import com.example.simplecalculator.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
    private enum Operator { NONE, ADD, SUB, MUL, DIV }

    private double opnd = 0;
    private double prev = opnd;
    private Operator operator = Operator.NONE;

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        binding.button0.setOnClickListener((v) -> appendDigit(0));
        binding.button1.setOnClickListener((v) -> appendDigit(1));
        binding.button2.setOnClickListener((v) -> appendDigit(2));
        binding.button3.setOnClickListener((v) -> appendDigit(3));
        binding.button4.setOnClickListener((v) -> appendDigit(4));
        binding.button5.setOnClickListener((v) -> appendDigit(5));
        binding.button6.setOnClickListener((v) -> appendDigit(6));
        binding.button7.setOnClickListener((v) -> appendDigit(7));
        binding.button8.setOnClickListener((v) -> appendDigit(8));
        binding.button9.setOnClickListener((v) -> appendDigit(9));

        binding.buttonAdd.setOnClickListener((v) -> setOperator(Operator.ADD));
        binding.buttonSub.setOnClickListener((v) -> setOperator(Operator.SUB));
        binding.buttonMul.setOnClickListener((v) -> setOperator(Operator.MUL));
        binding.buttonDiv.setOnClickListener((v) -> setOperator(Operator.DIV));

        binding.buttonCalc.setOnClickListener((v) -> {
            try {
                switch (operator) {
                    case ADD:
                        opnd = prev + opnd;
                        break;
                    case SUB:
                        opnd = prev - opnd;
                        break;
                    case MUL:
                        opnd = prev * opnd;
                        break;
                    case DIV:
                        opnd = prev / opnd;
                }

                binding.textResult.setText(toStringByDecimal(opnd));
            } catch (Exception e) {
                binding.textResult.setText("Err");
            } finally {
                prev = opnd;
                opnd = 0;
                operator = Operator.NONE;
            }
        });

        binding.buttonC.setOnClickListener((v) -> {
            opnd = 0;
            prev = 0;
            binding.textResult.setText("0");
        });
    }

    private void appendDigit(int a) {
        opnd = opnd * 10 + a;
        binding.textResult.setText(toStringByDecimal(opnd));
    }

    private void setOperator(Operator a) {
        operator = a;
        if (opnd != 0) {
            prev = opnd;
            opnd = 0;
        }
    }

    private String toStringByDecimal(double a) {
        if (a - (int)a == 0) {
            return "" + (int)a;
        } else{
            return "" + a;
        }
    }
}