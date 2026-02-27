import { Module } from '@nestjs/common';
import { SubjectsService } from './subjects.service';
import { SubjectsController } from './subjects.controller';
import { FileAccessor, FileService } from 'src/file.service';
import { Subject } from './entities/subject.entity';

@Module({
  controllers: [SubjectsController],
  providers: [
    SubjectsService,
    {
      provide: FileService,
      useFactory: (subjects: SubjectsModule) =>
        new FileService<Subject[]>(subjects.filePath),
      inject: [SubjectsModule],
    },
  ],
})
export class SubjectsModule implements FileAccessor {
  public readonly filePath = 'assets/subjects.json';
}
