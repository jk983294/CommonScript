-- (A, B) is primary key, (C, VERSION_CREATED_BY, VERSION_CREATED_TIME) are data 	
CREATE PROCEDURE SP_CREATE_SOMETHING (IN I_A VARCHAR(20),
                                     IN I_C VARCHAR(50),
                                     IN I_VERSION_CREATED_BY VARCHAR(20))
    SPECIFIC SP_CREATE_SOMETHING
    RESULT SETS 1
    MODIFIES SQL DATA
    NOT DETERMINISTIC
    NULL CALL
    LANGUAGE SQL EXTERNAL ACTION
    INHERIT SPECIAL REGISTERS
BEGIN
	DECLARE v_B INTEGER;
	DECLARE v_VERSION_CREATED_TIME TIMESTAMP;
	SELECT COUNT(B) INTO v_B FROM my_table where A = I_A;
	if v_B = 0 then 
		set v_B = 1;
	else 
		SELECT max(B) + 1 INTO v_B FROM my_table where A = I_A;
	end if;
	set v_VERSION_CREATED_TIME = current_timestamp;
	insert into my_table (A, B, C, VERSION_CREATED_BY, VERSION_CREATED_TIME) 
		values (I_A, v_B, I_C, I_VERSION_CREATED_BY, v_VERSION_CREATED_TIME);
BEGIN
