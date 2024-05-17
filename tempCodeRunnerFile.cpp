f (body.heart_rate <= 60) {
            cout << "Bradycardia - Here's some basic advices: " << endl;
            cout << get_info()["Heart rate"]["Bradycardia"] << endl;
        }
        else if (body.heart_rate >= 100) { 
            cout << "Tachycardia - Here's some basic advices: " << endl;
            cout << get_info()["Heart rate"]["Tachycardia"] << endl;
        }
        float BMI = body.weight / (body.height * body.height);
        if (BMI <= 18.5) {
            cout << "Underweight - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Underweight"].get<string>() << endl;
        }
        else if (BMI > 18.5 && BMI <= 24.9) {
            cout << "Normal Weight - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Normal Weight"].get<string>() << endl;
        }
        else if (BMI > 24.9 && BMI <= 30) {
            cout << "Overweight - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Overweight"].get<string>() << endl;
        }
        else {
            cout << "Obese - Here's some basic advice for that condition:\n";
            cout << get_info()["BMI"]["Obese"].get<string>() << endl;
        }
