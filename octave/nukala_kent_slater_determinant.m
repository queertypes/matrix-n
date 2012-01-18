function determinant = nukala_kent_slater_determinant(D, V, num_steps,
                                                      threshold)
  
  # Initialization
  num_electrons = rows(D);
  p = 0;
  gamma = zeros(1, num_steps);
  U = zeros(num_electrons, num_steps);
  step = 1;

  # Configuration stepping stage: Alg. 1
  while step < (num_steps + 1)
    p = mod(p, num_electrons) + 1;
    U(:,step) = D(:,p);
    for i = 1:step
      U(:,step) = U(:,step) - gamma(1,i) * (V(i,:) * U(:,step)) * U(:,step);
    endfor
    R = 1 + V(step,:) * U(:,step);
    if (abs(R) > threshold)
      gamma(1,step) = 1/R;
      ++step;
    endif
  endwhile

  # Final reduction stage: Eq. 11
  prod = eye(num_electrons, num_electrons);
  for i = 1:num_steps
    prod = prod * (eye(num_electrons, num_electrons) - gamma(1,i) * U(:,i) * V(i,:));
  endfor
  D_after = prod * D;

  # Return determinant of final step
  determinant = det(D_after);
endfunction
