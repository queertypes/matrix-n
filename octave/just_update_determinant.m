function determinant = just_update_determinant(D, V, num_steps)
	num_electrons = rows(D);
	D_after = D;
	D_curr = D;
	p = 0;

	# Simply perform row exchange,
	# calculate R as det(R') / det(R)
	for step=1:num_steps
		p = mod(p, num_electrons) + 1;
		D_after(p,:) = V(step, :);
		R = det(D_after) / det(D_curr);
		if (abs(R) > .99)
			D_curr = D_after;
		else
			step = step - 1;
		endif
	endfor

	# Return determinant of final step
	determinant = det(D_after);
endfunction
