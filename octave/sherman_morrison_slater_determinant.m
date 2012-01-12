function determinant = sherman_morrison_slater_determinant(D, V, num_steps)
	p = 0;
	num_electrons = rows(D);
	D_after = D;
	D_curr = D;
	
	for step=1:num_steps
		p = mod(p, num_electrons) + 1;
		R = (1 + V(step,:) * D_curr(:,p));
		D_after = D_curr - (D_curr(:,p) * V(step,:) * D_curr)/(R);
		if (R > .95)
			D_curr = D_after;
		else
			step = step - 1;
		endif
	endfor
	
	determinant = det(D_curr);
endfunction
