function determinants = test_slater_from_file(num_steps, num_electrons)
	determinants = zeros(1,3);
	D = rand(num_electrons, num_electrons);
	file_name = sprintf("data/V_%d_%d.hdf5", num_electrons, num_steps);
	load("-hdf5", file_name, "V");
	V = V';

	determinants(1,1) = nukala_kent_slater_determinant(D, V, num_steps);
	#determinant(1,2) = sherman_morrison_slater_determinant(D, V, num_steps);
	#determinant(1,3) = naive_slater_determinant(D, V, num_steps);
endfunction
