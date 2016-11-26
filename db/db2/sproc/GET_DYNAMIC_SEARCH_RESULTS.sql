CREATE OR REPLACE PROCEDURE schema.GET_DYNAMIC_SEARCH_RESULTS(
                                            IN P_PARAM1 VARCHAR(200) DEFAULT NULL,
                                            IN P_PARAM2 VARCHAR(200) DEFAULT NULL,
                                            IN P_PARAM3 VARCHAR(200) DEFAULT NULL)
    SPECIFIC schema.GET_DYNAMIC_SEARCH_RESULTS
    RESULT SETS 1
    MODIFIES SQL DATA
    NOT DETERMINISTIC
    NULL CALL
    LANGUAGE SQL EXTERNAL ACTION
    INHERIT SPECIAL REGISTERS
BEGIN
  DECLARE v_sql_str       VARCHAR(30000);
	DECLARE V_WHERE_CONDITION VARCHAR(3000);

	-- build where clause base on the parameters passed in
  set V_WHERE_CONDITION = ' where 1 = 1';
  IF P_PARAM1 IS NOT NULL THEN
    set V_WHERE_CONDITION = V_WHERE_CONDITION || ' and (t.PARAM1 = ''' || P_PARAM1 || ''') ';
  END IF;
  IF P_PARAM2 IS NOT NULL THEN
    set V_WHERE_CONDITION = V_WHERE_CONDITION || ' and (t.PARAM2 = ''' || P_PARAM2 || ''') ';
  END IF;
  IF P_PARAM3 IS NOT NULL THEN
    IF P_PARAM3 = 'Y' THEN
      set V_WHERE_CONDITION = V_WHERE_CONDITION || ' and (t.PARAM3 is not null) ';
    ELSEIF P_PARAM3 = 'N' THEN
      set V_WHERE_CONDITION = V_WHERE_CONDITION || ' and (t.PARAM3 is null) ';
    END IF;
  END IF;

  set v_sql_str = 'SELECT t.PARAM1, t.PARAM2,
                    case when t.PARAM3 is not null then ''Y'' else ''N'' end as PARAM3,
                    t.PARAM4, FROM my_table as t ' || V_WHERE_CONDITION || ' AND t.PARAM4 = ''some value''
                    ORDER BY t.PARAM1 DESC FETCH FIRST 100 ROWS ONLY WITH UR';
	BEGIN
    DECLARE process_cursor CURSOR WITH RETURN FOR s1;
    PREPARE s1 from v_sql_str;
    OPEN process_cursor;
	END;
END 
