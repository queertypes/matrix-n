function determinants = test_slater_from_file(num_steps, num_electrons)
	determinants = zeros(1,4);
	D = rand(num_electrons, num_electrons);
	file_name_V = sprintf("data/V_%d_%d.hdf5", num_electrons, num_steps);
	file_name_D = sprintf("data/D_%d_%d.hdf5", num_electrons, num_electrons);
	load("-hdf5", file_name_V, "V");
	load("-hdf5", file_name_D, "D");
	V = V';

	determinants(1,1) = nukala_kent_slater_determinant(D, V, num_steps);
	determinants(1,2) = sherman_morrison_slater_determinant(D, V, num_steps);
	#determinant(1,3) = naive_slater_determinant(D, V, num_steps);
	determinants(1,4) = just_update_determinant(D, V, num_steps);
	determinants;
	for i=1:4
		determinants(1,i)
	endfor
endfunction
