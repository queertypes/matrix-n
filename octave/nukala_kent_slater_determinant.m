function determinant = nukala_kent_slater_determinant(D, V, num_steps)
	
	# Initialization
	num_electrons = rows(D);
	p = 0;
	gamma = zeros(1, num_steps);
	U = zeros(num_electrons, num_steps);
	
	# Configuration stepping stage: Alg. 1
	for step = 1:num_steps
		p = mod(p, num_electrons) + 1;
		U(:,step) = D(:,p);
		for i = 1:step
			U(:,step) = U(:,step) - gamma(1,i) * (V(i,:) * U(:,step)) * U(:,step);
		endfor
		R = 1 + V(step,:) * U(:,step);
		if (abs(R) > .99)
			gamma(1,step) = 1/R;
		else
			step = step - 1;
		endif
	endfor

	# Final reduction stage: Eq. 11
	prod = eye(num_electrons, num_electrons);
	for i = 1:num_steps
		prod = prod * (eye(num_electrons, num_electrons) - gamma(1,i) * U(:,i) * V(i,:));
	endfor
	D_after = prod * D;

	# Return determinant of final step
	determinant = det(D_after);
endfunction
