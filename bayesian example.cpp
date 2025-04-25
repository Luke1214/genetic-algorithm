std::ofstream output_file("output.txt");

// Process each object in the testing data
for (int object = 0; object < testing_speed.size() / speeds_per_object; ++object) {
    std::vector<double> bird_prob(speeds_per_object, 0.5);  // Initialize with prior
    std::vector<double> airplane_prob(speeds_per_object, 0.5);

    for (int t = 0; t < speeds_per_object; ++t) {
        int speed_index = object * speeds_per_object + t;
        double speed = testing_speed[speed_index];

        // Calculate likelihood
        double bird_like = (speed >= 0 && speed < bird_likelihood.size()) ? bird_likelihood[static_cast<int>(speed)] : 0;
        double plane_like = (speed >= 0 && speed < airplane_likelihood.size()) ? airplane_likelihood[static_cast<int>(speed)] : 0;

        // Apply transition probabilities
        double bird_trans = 0.9 * bird_prob[t] + 0.1 * airplane_prob[t];
        double plane_trans = 0.9 * airplane_prob[t] + 0.1 * bird_prob[t];

        // Calculate posterior probabilities
        double bird_post = bird_like * bird_trans;
        double plane_post = plane_like * plane_trans;
        double total = bird_post + plane_post;

        // Normalize
        bird_prob[t] = bird_post / total;
        airplane_prob[t] = plane_post / total;

        // Classify this time step
        output_file << (bird_prob[t] > airplane_prob[t] ? "b" : "a") << "\n";
    }

    // Final classification for this object
    double avg_bird_prob = std::accumulate(bird_prob.begin(), bird_prob.end(), 0.0) / speeds_per_object;
    double avg_plane_prob = std::accumulate(airplane_prob.begin(), airplane_prob.end(), 0.0) / speeds_per_object;

    std::cout << "Object " << object + 1 << ": " << (avg_bird_prob > avg_plane_prob ? "Bird" : "Airplane") << "\n";
}

output_file.close();
