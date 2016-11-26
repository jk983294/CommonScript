-- for performance purpose, share the same temp table, two sub table query is against temp table
CREATE PROCEDURE SCHEMA.GET_MULTIPLY_DYNAMIC_RESULTS_USING_TMP_TABLE (IN I_PARAM0 VARCHAR(128),
                                                      IN I_PARAM1 VARCHAR(8),
                                                      IN I_PARAM2 VARCHAR(8),
                                                      IN I_PARAM3 VARCHAR(8),
                                                      IN I_QUERY_TYPE INTEGER)-- 0 both, 1 table A, 2 table B
  SPECIFIC SCHEMA.GET_MULTIPLY_DYNAMIC_RESULTS_USING_TMP_TABLE
  DYNAMIC RESULT SETS 2
  MODIFIES SQL DATA
  NOT DETERMINISTIC
  NULL CALL
  LANGUAGE SQL EXTERNAL ACTION
  INHERIT SPECIAL REGISTERS
BEGIN
  DECLARE v_sql_str       VARCHAR(30000);
  DECLARE V_WHERE_CONDITION VARCHAR(3000);
  DECLARE v_sql_str1       VARCHAR(30000);
  DECLARE V_WHERE_CONDITION1 VARCHAR(3000);

  -- Create temp table to store query results
  DECLARE GLOBAL TEMPORARY TABLE session.MY_SHARED_TEMP_TABLE as (
    SELECT  a.*, b.column1, b.column2 FROM MY_TABLE_X a INNER JOIN MY_TABLE_Y b ON a.x=b.x AND a.y=b.y
  ) DEFINITION ONLY WITH REPLACE ON COMMIT PRESERVE ROWS NOT LOGGED;

  INSERT INTO session.MY_SHARED_TEMP_TABLE
    SELECT  a.*, b.column1, b.column2 FROM MY_TABLE_X a INNER JOIN MY_TABLE_Y b ON a.x=b.x AND a.y=b.y;

  -- Update column based on aggregation
  MERGE INTO session.MY_SHARED_TEMP_TABLE AS TARGET
    USING (SELECT category1, category2, SUM(score) AS total_score
             FROM session.MY_SHARED_TEMP_TABLE
             GROUP BY category1, category2) AS SRC
      ON SRC.category1 = TARGET.category1
         AND SRC.category2 = TARGET.category2
    WHEN MATCHED THEN UPDATE
      SET	total_score_column = SRC.total_score;

	-- build where clause base on the parameters passed in
  set V_WHERE_CONDITION = ' where 1 = 1 ';
  set V_WHERE_CONDITION1 = ' where 1 = 1 ';

  -- table A filter
  IF I_PARAM0 IS NOT NULL THEN
    set V_WHERE_CONDITION = V_WHERE_CONDITION || ' and (UPPER(PARAM0) = UPPER(''' || I_PARAM0 || ''')) ';
  END IF;

  IF I_PARAM1 IS NOT NULL THEN
     IF I_PARAM1 = 'NA' THEN
       set V_WHERE_CONDITION = V_WHERE_CONDITION || ' and (PARAM1 is null) ';
     ELSE
       set V_WHERE_CONDITION = V_WHERE_CONDITION || ' and (UPPER(PARAM1) = UPPER(''' || I_PARAM1 || ''')) ';
     END IF;
  END IF;

  -- table B filter
  IF I_PARAM2 IS NOT NULL THEN
    set V_WHERE_CONDITION1 = V_WHERE_CONDITION1 || ' and (UPPER(PARAM2) = UPPER(''' || I_PARAM2 || ''')) ';
  END IF;

  IF I_PARAM3 IS NOT NULL THEN
    set V_WHERE_CONDITION1 = V_WHERE_CONDITION1 || ' and (UPPER(PARAM3) = UPPER(''' || I_PARAM3 || ''')) ';
  END IF;

  -- which table to query
  IF I_QUERY_TYPE = 1 THEN        -- table A only
    set V_WHERE_CONDITION1 = ' where ID = ''SHOULD NOT FOUND'' ';
  ELSEIF I_QUERY_TYPE = 2 THEN    -- table B only
    set V_WHERE_CONDITION = ' where ID = ''SHOULD NOT FOUND'' ';
  END IF;

  set v_sql_str = 'with filtered as (select * from session.MY_SHARED_TEMP_TABLE' || V_WHERE_CONDITION || ' )
                      select distinct COLUMN_DESIRED1, COLUMN_DESIRED2, COLUMN_DESIRED3 from filtered';

  set v_sql_str1 = 'select COLUMN_DESIRED4, COLUMN_DESIRED5, COLUMN_DESIRED6 from session.MY_SHARED_TEMP_TABLE' || V_WHERE_CONDITION1;

  BEGIN
    DECLARE process_cursor CURSOR WITH RETURN FOR s;
    PREPARE s from v_sql_str;
    OPEN process_cursor;
  END;

  BEGIN
    DECLARE process_cursor1 CURSOR WITH RETURN FOR s1;
    PREPARE s1 from v_sql_str1;
    OPEN process_cursor1;
  END;
END