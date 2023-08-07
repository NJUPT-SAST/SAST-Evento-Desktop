#ifndef REPOSITORYINJECTOR_H
#define REPOSITORYINJECTOR_H

#include <infrastructure/injection/dependencyinjector.h>
#include <infrastructure/http/HttpClient.h>
#include <domain/repository/Repository.h>
#include <infrastructure/repository/impl/RepositoryImpl.h>

using namespace QInjection;
using namespace AeaQt;

class RepositoryInjector
{
public:
  static Repository* repository()
  {
    return new RepositoryImpl;
  }

  static void init()
  {
    HttpClient::instance();
    QInjection::addSingleton(repository);
  }
};

#endif  // REPOSITORYINJECTOR_H
