function determinant = nukala_kent_slater_determinant(D, V, num_steps,
                                                      threshold)
  
  # Initialization
  num_electrons = rows(D);
  p = 0;
  gamma_var = zeros(1, num_steps);
  U = zeros(num_electrons, num_steps);
	I = eye(num_electrons, num_electrons);
  step = 1;
	D = inv(D);

  # Configuration stepping stage: Alg. 1
  while step < (num_steps + 1)
    p = mod(p, num_electrons) + 1;
    U(:,step) = D(:,p);
    for i = 1:step
      U(:,step) = U(:,step) - gamma_var(i) * (V(i,:) * U(:,step)) * U(:,i);
    endfor
    R = 1 + V(step,:) * U(:,step);
    if (abs(R) > threshold)
      gamma_var(step) = 1/R;
      ++step;
    endif
  endwhile

  # Final reduction stage: Eq. 11
  prod = I;
  for i = 1:num_steps
    prod *= (I - gamma_var(i) * U(:,i) * V(i,:));
  endfor
  D_after = prod * D;

  # Return determinant of final step
  determinant = det(inv(D_after));
endfunction
