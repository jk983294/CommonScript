CREATE OR REPLACE PROCEDURE SCHEMA.SP_GET_MULTIPLE_RESULTS (IN I_PARAM VARCHAR(20))
    SPECIFIC SCHEMA.SP_GET_MULTIPLE_RESULTS
    RESULT SETS 2
    READS SQL DATA
    NOT DETERMINISTIC
    NULL CALL
    LANGUAGE SQL EXTERNAL ACTION
    INHERIT SPECIAL REGISTERS
BEGIN
	DECLARE c1 CURSOR WITH RETURN TO CLIENT FOR
	select * from SCHEMA.table1 where param1 = I_PARAM;

	DECLARE c2 CURSOR WITH RETURN TO CLIENT FOR
	select * from SCHEMA.table2 where param1 = I_PARAM;

  OPEN c1;
  OPEN c2;
END



import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.jdbc.core.ResultSetExtractor;
import org.springframework.jdbc.core.SqlParameter;
import org.springframework.jdbc.core.SqlReturnResultSet;
import org.springframework.jdbc.object.StoredProcedure;
import org.springframework.stereotype.Component;
import javax.sql.DataSource;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Component
public class ModificationReportDao extends StoredProcedure {
    //call SCHEMA.SP_GET_MULTIPLE_RESULTS('param');
    private static final String SQL = "SCHEMA.SP_GET_MULTIPLE_RESULTS";

    @Autowired
    public ModificationReportDao(@Qualifier("SCHEMA") DataSource dataSource) {
        super(dataSource, SQL);
        declareParameter(new SqlParameter("I_PARAM", Types.VARCHAR));
        declareParameter(new SqlReturnResultSet("c1", new Result1Extractor()));
        declareParameter(new SqlReturnResultSet("c2", new Result2Extractor()));
        compile();
    }

    public Map<String, Object> getModificationReportResults(String param1) {
        Map<String, Object> resultSets = execute(param1);
        Map<String, Object> results = new HashMap<>();
        results.put("data1", (List<String>) resultSets.get("c1"));
        results.put("data2", (List<String>) resultSets.get("c2"));
        return results;
    }

    private static class Result1Extractor implements ResultSetExtractor<List<String>> {
        @Override
        public List<String> extractData(ResultSet rs) throws SQLException {
            List<String> results = new ArrayList<>();
            while (rs.next()) {
                results.add(rs.getString("DATA_FIELD1"));
            }
            return results;
        }
    }

    private static class Result2Extractor implements ResultSetExtractor<List<String>> {
        @Override
        public List<String> extractData(ResultSet rs) throws SQLException {
            List<String> results = new ArrayList<>();
            while (rs.next()) {
                results.add(rs.getString("DATA_FIELD2"));
            }
            return results;
        }
    }
}
