-- COB lock block all categories, one category can block COB lock
-- CATEGORY2 is resource, one CATEGORY1 has several CATEGORY2
-- MY_TABLE_STATUS (CATEGORY1, COB, LOCKED_BY, UNLOCKED_BY, UPDATED_TIME, RESOURCE_NAME, COUNT, EXPIRE_TIME)

CREATE OR REPLACE PROCEDURE schema.SP_MY_GET_LOCK (IN I_CATEGORY1 VARCHAR(20),
                                                 IN I_COB INTEGER,
                                                 IN I_RESOURCE_NAME VARCHAR(50),
                                                 IN I_LOCKED_BY VARCHAR(20))
    SPECIFIC schema.SP_MY_GET_LOCK
    RESULT SETS 1
    MODIFIES SQL DATA
    NOT DETERMINISTIC
    NULL CALL
    LANGUAGE SQL EXTERNAL ACTION
    INHERIT SPECIAL REGISTERS
BEGIN
  DECLARE v_DURATION_SECONDS INTEGER default 864000; -- 10 days
  DECLARE v_LOCK_EXPIRED_COUNT INTEGER;
  DECLARE v_RESOURCE_LEFT_COUNT INTEGER;
	DECLARE v_CATEGORY2_COUNT INTEGER;
	DECLARE v_LOCK_RECORD_COUNT INTEGER;  -- check if there are records there, if no, first caller should create those records
	select count(*) INTO v_LOCK_RECORD_COUNT from schema.MY_TABLE_STATUS where CATEGORY1 = I_CATEGORY1 and COB = I_COB;

  -- release lock by expire day
  select count(*) INTO v_LOCK_EXPIRED_COUNT from schema.MY_TABLE_STATUS
    where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME != 'All'
      and COUNT = 0 and EXPIRE_TIME is not null and EXPIRE_TIME < current_timestamp;
  if v_LOCK_EXPIRED_COUNT > 0 then
    update schema.MY_TABLE_STATUS set COUNT = 1 where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME != 'All'
      and COUNT = 0 and EXPIRE_TIME is not null and EXPIRE_TIME < current_timestamp;
    -- return count to All
    update schema.MY_TABLE_STATUS set COUNT = (COUNT + v_LOCK_EXPIRED_COUNT)
      where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME = 'All';
  end if;

  -- lock process
  select count(*) INTO v_CATEGORY2_COUNT from (select distinct CATEGORY2 from schema.MY_TABLE);
  -- first locker create all records for that cob
  if v_LOCK_RECORD_COUNT = 0 then
    insert into schema.MY_TABLE_STATUS (CATEGORY1, COB, LOCKED_BY, UNLOCKED_BY, UPDATED_TIME, RESOURCE_NAME, COUNT, EXPIRE_TIME)
      select CATEGORY1, COB, null, null, null, CATEGORY2, 1, null
      from (select I_CATEGORY1 CATEGORY1, I_COB COB from dual), (select distinct CATEGORY2 from schema.MY_TABLE);
    insert into schema.MY_TABLE_STATUS (CATEGORY1, COB, LOCKED_BY, UNLOCKED_BY, UPDATED_TIME, RESOURCE_NAME, COUNT, EXPIRE_TIME)
      values (I_CATEGORY1, I_COB, null, null, null, 'All', v_CATEGORY2_COUNT, null);
  end if;

  select COUNT INTO v_RESOURCE_LEFT_COUNT from schema.MY_TABLE_STATUS where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME = I_RESOURCE_NAME;

  -- get COB lock
  if I_RESOURCE_NAME = 'All' then
    if v_RESOURCE_LEFT_COUNT = v_CATEGORY2_COUNT then -- acquire All lock
      update schema.MY_TABLE_STATUS set COUNT = 0, LOCKED_BY = I_LOCKED_BY, UPDATED_TIME = current_timestamp, EXPIRE_TIME = null
        where CATEGORY1 = I_CATEGORY1 and COB = I_COB;
      -- update locked_by field to differentiate all resource are required case
      update schema.MY_TABLE_STATUS set LOCKED_BY = 'COB Locker'
        where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME != 'All';
    end if;
  else -- get resource lock
    if v_RESOURCE_LEFT_COUNT = 1 then -- if resource lock is available, it means All is not locked
      update schema.MY_TABLE_STATUS set COUNT = 0, LOCKED_BY = I_LOCKED_BY, UPDATED_TIME = current_timestamp, EXPIRE_TIME = (current_timestamp + v_DURATION_SECONDS seconds)
        where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME = I_RESOURCE_NAME;
      -- burn down All count by 1
      update schema.MY_TABLE_STATUS set COUNT = COUNT - 1, LOCKED_BY = null
        where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME = 'All';
    end if;
  end if;

BEGIN
	-- return all lock result, because we need someone editing info for further infer
  DECLARE c1 CURSOR WITH RETURN TO CLIENT FOR
  select * from schema.MY_TABLE_STATUS where CATEGORY1 = I_CATEGORY1 and COB = I_COB;
  OPEN c1;
END;
END


CREATE OR REPLACE PROCEDURE schema.SP_MY_RELEASE_LOCK (IN I_CATEGORY1 VARCHAR(20),
                                                 IN I_COB INTEGER,
                                                 IN I_RESOURCE_NAME VARCHAR(50),
                                                 IN I_UNLOCKED_BY VARCHAR(20))
    SPECIFIC schema.SP_MY_RELEASE_LOCK
    RESULT SETS 1
    MODIFIES SQL DATA
    NOT DETERMINISTIC
    NULL CALL
    LANGUAGE SQL EXTERNAL ACTION
    INHERIT SPECIAL REGISTERS
BEGIN
  DECLARE v_RESOURCE_LEFT_COUNT INTEGER;
	DECLARE v_CATEGORY2_COUNT INTEGER;
	DECLARE v_LOCKED_BY VARCHAR(20);
	DECLARE v_LOCKED_BY_COB_COUNT INTEGER;
	DECLARE v_LOCK_RECORD_COUNT INTEGER;
	select count(*) INTO v_LOCK_RECORD_COUNT from schema.MY_TABLE_STATUS where CATEGORY1 = I_CATEGORY1 and COB = I_COB;
	select COUNT, LOCKED_BY INTO v_RESOURCE_LEFT_COUNT, v_LOCKED_BY from schema.MY_TABLE_STATUS where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME = I_RESOURCE_NAME;

  if v_LOCK_RECORD_COUNT > 0 and v_RESOURCE_LEFT_COUNT = 0 and v_LOCKED_BY = I_UNLOCKED_BY then
    select count(*) INTO v_CATEGORY2_COUNT from (select distinct CATEGORY2 from schema.MY_TABLE);
    select count(*) INTO v_LOCKED_BY_COB_COUNT from schema.MY_TABLE_STATUS where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME != 'All';
    if I_RESOURCE_NAME = 'All' and v_LOCKED_BY_COB_COUNT = v_CATEGORY2_COUNT then   -- release COB lock
      -- release all All count
      update schema.MY_TABLE_STATUS set COUNT = v_CATEGORY2_COUNT, UNLOCKED_BY = I_UNLOCKED_BY, UPDATED_TIME = current_timestamp, EXPIRE_TIME = null, LOCKED_BY = null
        where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME = 'All';
      update schema.MY_TABLE_STATUS set COUNT = 1, UNLOCKED_BY = I_UNLOCKED_BY, UPDATED_TIME = current_timestamp, EXPIRE_TIME = null, LOCKED_BY = null
          where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME != 'All';
    else -- release resource lock
      -- release All count by 1
      update schema.MY_TABLE_STATUS set COUNT = COUNT + 1
        where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME = 'All';
      update schema.MY_TABLE_STATUS set COUNT = 1, UNLOCKED_BY = I_UNLOCKED_BY, UPDATED_TIME = current_timestamp, EXPIRE_TIME = null
        where CATEGORY1 = I_CATEGORY1 and COB = I_COB and RESOURCE_NAME = I_RESOURCE_NAME;
    end if;
  end if;

BEGIN
	-- return all lock result, because we need someone editing info for further infer
  DECLARE c1 CURSOR WITH RETURN TO CLIENT FOR
  select * from schema.MY_TABLE_STATUS where CATEGORY1 = I_CATEGORY1 and COB = I_COB;
  OPEN c1;
END;
END

package com.victor.utilities.lock;

import org.apache.commons.collections.CollectionUtils;
import org.apache.log4j.Logger;
import org.springframework.stereotype.Component;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;


@Component
public class LockService {

    Logger logger = Logger.getLogger(LockService.class);

    /**
     * acquire lock for specified resource
     */
    public synchronized LockInfo getLock(String category1, String resource, String user, Integer cob){
        List<LockStatus> data = callSprocAndGetData("schema.SP_MY_GET_LOCK");
        LockInfo lockInfo = new LockInfo(category1, resource, user, cob);
        return getLockResult(data, lockInfo);
    }

    /**
     * release lock for specified resource
     */
    public synchronized LockInfo releaseLock(String category1, String resource, String user, Integer cob){
        List<LockStatus> data = callSprocAndGetData("schema.SP_MY_RELEASE_LOCK");
        LockInfo lockInfo = new LockInfo(category1, resource, user, cob);
        return getLockResult(data, lockInfo);
    }

    /**
     * Locks or unlocks COB
     * @return
     */
    public LockInfo updateCobLockStatus(LockInfo lockInfo) throws Exception {
        if(lockInfo.getHasLock()){
            return getLock(lockInfo.getCategory1(), lockInfo.getResourceName(), lockInfo.getUser(), lockInfo.getCobDate());
        } else {
            return releaseLock(lockInfo.getCategory1(), lockInfo.getResourceName(), lockInfo.getUser(), lockInfo.getCobDate());
        }
    }

    /**
     * Locks or unlocks the given resource
     * lockFlag true means try to get lock, false means try to release lock
     * @return
     */
    public LockInfo updateResourceLockStatus(LockInfo lockInfo, boolean lockFlag) throws IOException {
        if(lockFlag){
            return getLock(lockInfo.getCategory1(), lockInfo.getResourceName(), lockInfo.getUser(), lockInfo.getCobDate());
        } else {
            return releaseLock(lockInfo.getCategory1(), lockInfo.getResourceName(), lockInfo.getUser(), lockInfo.getCobDate());
        }
    }

    /**
     * get that cob lock status, locked / unlocked by who etc.
     */
    public LockInfo getCobLockStatus(String category1, Integer cob){
        LockInfo lockInfo = new LockInfo(category1, "All", null, cob);
        List<LockStatus> data = getStatusesFromDB(category1, cob);
        if(CollectionUtils.isNotEmpty(data)){
            for(LockStatus status : data){
                if("All".equals(status.getResourceName())){
                    if(status.getCount() > 0){
                        lockInfo.setHasLock(false);
                        break;
                    } else {
                        lockInfo.setHasLock(true);
                        lockInfo.setUser(status.getLockedBy());
                    }
                } else if(status.getCount() > 0 || !("COB Locker".equals(status.getLockedBy()))){
                    lockInfo.setHasLock(false);
                    break;
                }
            }
        } else {
            lockInfo.setHasLock(false);
        }
        return lockInfo;
    }

    /**
     * get that resource lock status, locked / unlocked by who etc.
     */
    public LockInfo getResourceLockStatus(String category1, Integer cob, String resource, String user){
        LockInfo lockInfo = new LockInfo(category1, resource, user, cob);
        return getLockResult(getStatusesFromDB(category1, cob), lockInfo);
    }

    /**
     * set hasLock field based on returned result
     */
    private LockInfo getLockResult(List<LockStatus> statuses, LockInfo lockInfo){
        if(CollectionUtils.isEmpty(statuses)){
            lockInfo.setErrorMessage("Failed to retrieve lock info from DB.");
            lockInfo.setHasLock(false);
        } else {
            LockStatus targetLockStatus = null, anyNonTargetsHasLockStatus = null;
            boolean anyNonTargetsHasLock = false;
            for(LockStatus status : statuses){
                if(lockInfo.getResourceName().equals(status.getResourceName())){
                    targetLockStatus = status;
                } else if(status.getCount() == 0){
                    anyNonTargetsHasLock = true;
                    anyNonTargetsHasLockStatus = status;
                }
            }
            if(targetLockStatus == null){
                lockInfo.setErrorMessage("Failed to retrieve lock info from DB.");
                lockInfo.setHasLock(false);
            } else if(targetLockStatus.getCount() > 0){
                if("All".equals(lockInfo.getResourceName()) && anyNonTargetsHasLock){
                    lockInfo.setErrorMessage("Cannot lock due to " + anyNonTargetsHasLockStatus.getResourceName() + " is under editing by " + anyNonTargetsHasLockStatus.getLockedBy());
                }
                lockInfo.setHasLock(false);
            } else if(lockInfo.getUser().equals(targetLockStatus.getLockedBy())){
                lockInfo.setHasLock(true);
            } else {
                if("All".equals(lockInfo.getResourceName()) && anyNonTargetsHasLock){
                    lockInfo.setErrorMessage("Cannot lock due to " + anyNonTargetsHasLockStatus.getResourceName() + " is under editing by " + anyNonTargetsHasLockStatus.getLockedBy());
                } else {
                    lockInfo.setErrorMessage("Cannot get lock due to " + targetLockStatus.getResourceName() + " is under editing by " + targetLockStatus.getLockedBy());
                }
                lockInfo.setHasLock(false);
            }
        }
        return lockInfo;
    }

    private List<LockStatus> getStatusesFromDB(String category1, Integer cob) {
        StringBuilder filter = new StringBuilder();
        filter.append(" cob = ").append(cob).append(" and category1 = '").append(category1).append("'");
        return null;    // fake one
    }

    private List<LockStatus> callSprocAndGetData(String sprocName) {
        List<LockStatus> statuses = new ArrayList<>();
        new LockStatusExtractor(statuses);
        return statuses;    // fake one
    }
}


package com.victor.utilities.lock;

import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.ResultSetExtractor;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

/**
 * extract data from sql result set
 */
public class LockStatusExtractor implements ResultSetExtractor {

    private List<LockStatus> lockStatuses;

    public LockStatusExtractor(List<LockStatus> statusVOs) {
        this.lockStatuses = statusVOs;
    }

    @Override
    public List<LockStatus> extractData(ResultSet rs) throws SQLException, DataAccessException {
        while (rs.next()) {
            LockStatus status = new LockStatus();
            status.setCategory1(rs.getString("CATEGORY1"));
            status.setCobDate(rs.getInt("COB_DATE"));
            status.setLockedBy(rs.getString("LOCKED_BY"));
            status.setUnlockedBy(rs.getString("UNLOCKED_BY"));
            status.setUpdatedTime(rs.getDate("UPDATED_TIME"));
            status.setResourceName(rs.getString("RESOURCE_NAME"));
            status.setCount(rs.getInt("COUNT"));
            if(rs.wasNull()){
                status.setCount(null);
            }
            status.setExpireTime(rs.getTimestamp("EXPIRE_TIME"));
            lockStatuses.add(status);
        }
        return lockStatuses;
    }
}


package com.victor.utilities.lock;

import java.sql.Timestamp;
import java.util.Date;

public class LockStatus {

    private String category1;

    private Integer cobDate;

    private String lockedBy;

    private String unlockedBy;

    private Date updatedTime;

    private String resourceName;

    private Integer count;

    private Timestamp expireTime;

    public String getCategory1() {
        return category1;
    }

    public void setCategory1(String category1) {
        this.category1 = category1;
    }

    public Integer getCobDate() {
        return cobDate;
    }

    public void setCobDate(Integer cobDate) {
        this.cobDate = cobDate;
    }

    public String getLockedBy() {
        return lockedBy;
    }

    public void setLockedBy(String lockedBy) {
        this.lockedBy = lockedBy;
    }

    public String getUnlockedBy() {
        return unlockedBy;
    }

    public void setUnlockedBy(String unlockedBy) {
        this.unlockedBy = unlockedBy;
    }

    public Date getUpdatedTime() { return updatedTime; }

    public void setUpdatedTime(Date updatedTime) { this.updatedTime = updatedTime; }

    public String getResourceName() {
        return resourceName;
    }

    public void setResourceName(String resourceName) {
        this.resourceName = resourceName;
    }

    public Integer getCount() {
        return count;
    }

    public void setCount(Integer count) {
        this.count = count;
    }

    public Timestamp getExpireTime() {
        return expireTime;
    }

    public void setExpireTime(Timestamp expireTime) {
        this.expireTime = expireTime;
    }
}


package com.victor.utilities.lock;

/**
 * lock results
 */
public class LockInfo {

    private String category1;

    private String resourceName;

    private String user;

    private Integer cobDate;

    private Boolean hasLock = false;

    private String errorMessage;

    public LockInfo(String category1, String resourceName, String user, Integer cobDate) {
        this.category1 = category1;
        this.resourceName = resourceName;
        this.user = user;
        this.cobDate = cobDate;
    }

    public LockInfo() {
    }

    public String getCategory1() {
        return category1;
    }

    public void setCategory1(String category1) {
        this.category1 = category1;
    }

    public String getResourceName() {
        return resourceName;
    }

    public void setResourceName(String resourceName) {
        this.resourceName = resourceName;
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public Integer getCobDate() {
        return cobDate;
    }

    public void setCobDate(Integer cobDate) {
        this.cobDate = cobDate;
    }

    public Boolean getHasLock() {
        return hasLock;
    }

    public void setHasLock(Boolean hasLock) {
        this.hasLock = hasLock;
    }

    public String getErrorMessage() {
        return errorMessage;
    }

    public void setErrorMessage(String errorMessage) {
        this.errorMessage = errorMessage;
    }
}
