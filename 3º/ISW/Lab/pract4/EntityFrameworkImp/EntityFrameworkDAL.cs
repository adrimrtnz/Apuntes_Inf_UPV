using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Linq.Expressions;

namespace Magazine.Persistence
{
    public class EntityFrameworkDAL : IDAL
    {
        private readonly DbContextISW dbContext;

        public EntityFrameworkDAL(DbContextISW dbContext)
        {
            this.dbContext = dbContext;
        }

        public void Insert<T>(T entity) where T : class
        {
            dbContext.Set<T>().Add(entity);
        }

        public void Delete<T>(T entity) where T : class
        {
            dbContext.Set<T>().Remove(entity);
        }

        public IEnumerable<T> GetAll<T>() where T : class
        {
            return dbContext.Set<T>();
        }

        public T GetById<T>(IComparable id) where T : class
        {
            return dbContext.Set<T>().Find(id);
        }

        public bool Exists<T>(IComparable id) where T : class
        {
            return dbContext.Set<T>().Find(id) != null;
        }

        public void Clear<T>() where T : class
        {
            dbContext.Set<T>().RemoveRange(dbContext.Set<T>());
        }

        public IEnumerable<T> GetWhere<T>(Expression<Func<T, bool>> predicate) where T : class
        {
            return dbContext.Set<T>().Where(predicate).AsEnumerable();
        }

        public void Commit()
        {
            dbContext.SaveChanges();
        }

        public void Rollback() {
            dbContext.Rollback();
        }

        public void RemoveAllData()
        {
            dbContext.RemoveAllData();
        }

        DbContextTransaction _transaction;
        public void BeginTransaction()
        {
            _transaction = dbContext.Database.BeginTransaction();
        }

        // Sería mejor cambiar el nombre al metodo Commit y dejarlo como SaveChanges()
        public void CommitTransaction()
        {
            _transaction.Commit();
        }

        public void RollbackTransaction()
        {
            _transaction.Rollback();
        }
    }
}
