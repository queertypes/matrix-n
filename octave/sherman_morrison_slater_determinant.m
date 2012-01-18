function determinant = sherman_morrison_slater_determinant(D, V, num_steps,
                                                           threshold)
  p = 0;
  num_electrons = rows(D);
  D_after = D;
  D_curr = D;
	step = 1;

  while step < (num_steps + 1)
    p = mod(p, num_electrons) + 1;

    # Calculate R as Eq. 8
    R = (1 + V(step,:) * D_curr(:,p));

    if (abs(R) > threshold)
      # Calculate D' as Eq. 9 and update current configuration
			D_after = D_curr - (D_curr(:,p) * V(step,:) * D_curr)/(R);
      D_curr = D_after;
			++step;
    endif
  endwhile

  # Return determinant of final step
  determinant = det(D_curr);
endfunction
