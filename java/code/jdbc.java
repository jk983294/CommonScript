public class jdbc {

    public List<String> getSomething(String sql) throws SQLException {
        List<String> data = getJdbcTemplate().query(sql, new RowMapper<String>(){
            public String mapRow(ResultSet rs, int rowNum) throws SQLException {
                return rs.getString("fieldName");
            }
        });
        return data;
    }

    public Pojo getSomething(String field1, String field2) throws Exception {
        String sql = "call schema.get_something(?, ?)";
        Pojo pojo = null;
        try {
            pojo = jdbcTemplate.queryForObject(sql, new RowMapper<Pojo>() {
                public Pojo mapRow(ResultSet rs, int rowNum) throws SQLException {
                    Pojo pojo = new Pojo();
                    pojo.setField1(rs.getInt("field1"));
                    pojo.setField2(rs.getString("field2"));
                    return pojo;
                }
            }, field1, field2);
        } catch (Exception e) {
            logger.error("No pojo found for field1 " + field1 + ", field2 " + field2);
            throw e;
        }
        return pojo;
    }

    public List<Pojo> getSomethingList(String field1, String field2) {
        String sql = "call schema.get_something_list(?, ?)";
        List<Pojo> pojoes = new ArrayList<>();
        try {
            pojoes = jdbcTemplate.query(sql, new Object[]{field1, field2},
                    new RowMapper<Pojo>() {
                        public Pojo mapRow(ResultSet rs, int rowNum) throws SQLException {
                            Pojo pojo = new Pojo();
                            pojo.setField1(rs.getInt("field1"));
                            pojo.setField2(rs.getString("field2"));
                            return pojo;
                        }
                    });
        } catch (Exception e) {
            logger.error("get results failed", e);
            throw e;
        }
        return pojoes;
    }

    public void updateSomething(Pojo pojo){
        String sql = "call schema.save_something(?, ?)";
        try {
            jdbcTemplate.update(sql, pojo.getField1(), pojo.getField2());
        } catch (Exception e) {
            logger.error("update failed.");
            throw e;
        }
    }

    public void updateSomething(MyObject myObject) {
        String sql = "UPDATE schema.table SET x = ?, y = ? WHERE a = ? and  b = ?";
        jdbcTemplate.update(sql, myObject.getX(), myObject.getY(), myObject.getA(), myObject.getB());
    }

    public void updateSomethingBatchly(final List<MyObject> myObjects) {
        String sql = "UPDATE schema.table SET x = ?, y = ? WHERE a = ? and  b = ?";
        jdbcTemplate.batchUpdate(sql, new BatchPreparedStatementSetter() {
            @Override
            public void setValues(PreparedStatement ps, int i) throws SQLException {
                MyObject myObject = myObjects.get(i);
                if(myObject.getX() == null){
                    ps.setNull(1, Types.DOUBLE);
                } else {
                    ps.setDouble(1, myObject.getX());
                }
                if(myObject.getY() == null){
                    ps.setNull(2, Types.DOUBLE);
                } else {
                    ps.setDouble(2, myObject.getY());
                }
                ps.setInt(3, myObject.getA());
                ps.setString(4, myObject.getB());
            }
            @Override
            public int getBatchSize() {
                return myObjects.size();
            }
        });
    }
}