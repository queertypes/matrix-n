function determinant = nukala_kent_slater_determinant(D, V, num_steps)
	
endfunction


function slater_determinant = nukala_slater_determinant(D, v, num_steps,
                                                        threshold)
  num_electrons = rows(D);
  u = zeros(num_electrons, num_steps);
  V = zeros(num_electrons, num_steps);
  V(:,1) = v;
  gamma = zeros(1, num_steps);
  
  slater_determinant = _nukala_slater_iterate(D, V, u, gamma, 
                                              num_electrons, num_steps,
                                              threshold);
endfunction

function slater_determinant = _nukala_slater_recurse(D, v, u, gamma, 
                                                     num_electrons, num_steps, 
                                                     p, k, threshold) 
  if k == num_steps
    slater_determinant = det((eye(num_electrons) - 
                              gamma(1,k) * u(:, k) * v'(k,:)) * det(D));
  else
    v(:, k) = rand(num_electrons, 1);
    u(:, k) = D(:, p);
    for i = 1:k-1
      u(:, k) = u(:, k) - gamma(1,i) * (v'(k, :) * u(:, k)) * u(:, i);
    endfor
    R = 1 + v'(k, :) * u(:, k);
    if R > threshold
      gamma(1,k) = 1.0 / R;
      k = k + 1;
    endif
    slater_determinant = _nukala_slater_recurse(D, v, u, gamma, num_electrons,
                                                num_steps, 
                                                mod(p,num_electrons) + 1, 
                                                k);
  endif
endfunction

function slater_determinant = _nukala_slater_iterate(D, v, u, gamma, 
                                                     num_electrons, num_steps, 
                                                     threshold)
  k = 1;
  p = 1;
  while (k != num_steps)
    p = mod(p, num_electrons) + 1;
    v(:, k) = rand(num_electrons, 1);
    u(:, k) = D(:, p);
    for i = 1:k-1
      u(:, k) = u(:, k) - gamma(1,i) * (v'(k, :) * u(:, k)) * u(:, i);
    endfor
    R = 1 + v'(k, :) * u(:, k);
    if R > threshold
      gamma(1,k) = 1.0 / R;
      k = k + 1;
    endif
  endwhile
  
  slater_determinant = det((eye(num_electrons) - 
                            gamma(1,k) * u(:, k) * v'(k,:)) * det(D));
endfunction
