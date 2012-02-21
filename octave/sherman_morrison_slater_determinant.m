 function determinant = sherman_morrison_slater_determinant(D, V, num_steps, threshold)
  p = 0;
  num_electrons = rows(D);

	# begin with all matrices inverted, as algorithm works
	# on inverse matrices
  iD = inv(D);
	step = 1;

  while step < (num_steps + 1)
    p = mod(p, num_electrons) + 1;

    R = (1 + V(step,:) * iD(:,p));

    if (abs(R) > threshold)
			iD = iD - (iD(:,p) * (V(step,:) * iD))/(R);
			++step;
    endif
  endwhile

  # Return determinant of final step
	D_sherman = inv(iD)
  determinant = det(inv(iD));
endfunction
