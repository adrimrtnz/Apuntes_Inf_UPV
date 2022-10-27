using Magazine.Entities;
using System;
using System.Data.Entity;
using System.Reflection;
using System.Linq;
using System.Reflection.Emit;
using System.Data.Entity.ModelConfiguration.Conventions;

namespace Magazine.Persistence
{
    public class MagazineDbContext : DbContextISW
    {
        public MagazineDbContext() : base("MagazineDbConnection") //this is the connection string name
        {
            /*
            See DbContext.Configuration documentation
            */
            Configuration.ProxyCreationEnabled = true;
            Configuration.LazyLoadingEnabled = true;
        }

        static MagazineDbContext()
        {
            //Database.SetInitializer<BikeClubDbContext>(new CreateDatabaseIfNotExists<MagazineDbContext>());
            Database.SetInitializer<MagazineDbContext>(new DropCreateDatabaseIfModelChanges<MagazineDbContext>());
            //Database.SetInitializer<BikeClubDbContext>(new DropCreateDatabaseAlways<MagazineDbContext>());
        }

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Paper>()
                        .HasRequired(p => p.Responsible)
                        .WithMany()
                        .WillCascadeOnDelete(false);
        }


        // DbSets for persistent classes in your case study
        public DbSet<Person> People { get; set; }
        public DbSet<User> Users { get; set; }
        public DbSet<Magazine.Entities.Magazine> Magazines { get; set; }
        public DbSet<Area> Areas { get; set; }
        public DbSet<Paper> Papers { get; set; }
        public DbSet<Evaluation> Evaluations { get; set; }
        public DbSet<Issue> Issues { get; set; }


        // Generic method to clear all the data (except some relations if needed)
        public override void RemoveAllData()
        {
            clearSomeRelationships();
            // Esto no funciona en este modelo porque genera un borrado en cascada
            // al borrar primero Area. Este borrado en cascada provoca error en el test de persistencia TestPaper
            // cuando base.RemoveAllData() intenta borrar entidades ya marcadas como deleted
            // base.RemoveAllData();

            // Para solucionar el error hacemos el borrado explícitamente en un orden concreto
            // dejando Area para el final cuando todo lo demás se ha borrado

            Set<Person>().RemoveRange(Set<Person>());
            Set<Paper>().RemoveRange(Set<Paper>());
            Set<Evaluation>().RemoveRange(Set<Evaluation>());
            Set<Issue>().RemoveRange(Set<Issue>());
            Set<User>().RemoveRange(Set<User>());   
            Set<Magazine.Entities.Magazine>().RemoveRange(Set<Magazine.Entities.Magazine>());            
            Set<Area>().RemoveRange(Set<Area>());
            
            
            SaveChanges();
        }

        // Sometimes it is needed to clear some relationships explicitly 
        private void clearSomeRelationships()
        {
            
        }

    }

}
