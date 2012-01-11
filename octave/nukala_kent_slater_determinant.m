function determinant = nukala_kent_slater_determinant(D, V, num_steps)
	
	printf("Start\n");

	# Initialization
	num_electrons = rows(D);
	p = 1;
	step = 1;
	gamma = zeros();
	U = zeros(num_steps, num_electrons);

	# Iterative refinement stage
	for step = 1:num_steps
		printf("Here: step(%d)\n", step);
		p = mod(p, num_electrons) + 1;
		U(step,:) = D(:,p);
		for i = 1:step-1
			U(step,:) = U(step,:) - gamma(1,i) * (V(i,:) * U(step,:)) * U(i,:);
		endfor
		R = 1 + V(step,:) * U(step,:);
		gamma(1,step) = 1/R;
		k = k + 1;
	endfor
	D_after = 0;

	# Final reduction stage
	prod = eye(num_electrons, num_electrons);
	for i = 0:num_steps
		prod = prod * (eye(num_electrons, num_electrons) - gamma(1,i) * U(,:) * V(i,:));
	endfor
	D_after = prod * D;

	determinant = det(D_after);
endfunction
