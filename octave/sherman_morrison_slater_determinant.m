function determinant = sherman_morrison_slater_determinant(D, V, num_steps, 
                                                           threshold)
  p = 0;
  num_electrons = rows(D);
  D_after = D;
  D_curr = D;
  
  for step=1:num_steps
    p = mod(p, num_electrons) + 1;

    # Calculate R as Eq. 8
    R = (1 + V(step,:) * D_curr(:,p));

    # Calculate D' as Eq. 9
    D_after = D_curr - (D_curr(:,p) * V(step,:) * D_curr)/(R);
    if (abs(R) > threshold)
      D_curr = D_after;
    else
      step = step - 1;
    endif
  endfor

  # Return determinant of final step
  determinant = det(D_curr);
endfunction
