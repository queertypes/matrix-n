function determinant = just_update_determinant(D, V, num_steps, threshold)
  num_electrons = rows(D);
  D_after = D;
  D_curr = D;
  p = 0;
  step = 1;

  # Simply perform row exchange,
  # calculate R as det(new_R) / det(old_R)
  while step < (num_steps + 1)
    p = mod(p, num_electrons) + 1;
    D_after(p,:) += V(step, :);
    R = det(D_after) / det(D_curr);

    if (abs(R) > threshold)
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
	D_just = D_after
  determinant = det(D_after);
endfunction
