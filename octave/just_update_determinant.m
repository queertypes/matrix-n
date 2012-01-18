function determinant = just_update_determinant(D, V, num_steps)
	num_electrons = rows(D);
	D_after = D;
	D_curr = D;
	p = 0;
	step = 1;

	# Simply perform row exchange,
	# calculate R as det(R') / det(R)
  while step != num_steps
		p = mod(p, num_electrons) + 1;
		D_after(p,:) = V(step, :);
		R = det(D_after) / det(D_curr);

		if (abs(R) > .99)
			# update current Slater matrix with accepted
			# configuration and advance time step
			D_curr(p,:) = D_after(p,:);
			++step;
		else
			# revert change on future Slater matrix
			D_after(p,:) = D_curr(p,:);
		endif
	endwhile

	# Return determinant of final step
	determinant = det(D_curr);
endfunction
